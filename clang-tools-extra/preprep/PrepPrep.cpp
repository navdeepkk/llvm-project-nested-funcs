#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace clang::SrcMgr;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;
using namespace clang;
using namespace std;
using namespace clang::driver;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp("\nMore help text...\n");
//----------------------------------------------------global
// decls----------------------------------------------//
std::vector<std::string> labels;
//------------------------------------------------/global decls
// end-------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
class TypedefRenamer : public MatchFinder::MatchCallback {
public:
  TypedefRenamer(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const TypedefDecl *td =
            Result.Nodes.getNodeAs<clang::TypedefDecl>("typedef")) {
      auto beginloc = td->getBeginLoc();
      auto endloc = td->getEndLoc();
      std::string tdname = td->getUnderlyingType().getAsString();
      // if struct is not present in theunderlying type not the
      // canonical type the remove this typedef.
      if (tdname.find("struct") == std::string::npos) {
        Rewrite.ReplaceText(td->getSourceRange(), "");
        auto loc = clang::Lexer::findNextToken(endloc, Rewrite.getSourceMgr(),
                                               Rewrite.getLangOpts())
                       ->getLocation();

        Rewrite.ReplaceText(loc, "");
      } else {
        // replace the typedef with struct + structname. and remove
        // the struct name from the end;
        Rewrite.ReplaceText(beginloc, "");
        auto loc = clang::Lexer::findNextToken(beginloc, Rewrite.getSourceMgr(),
                                               Rewrite.getLangOpts())
                       ->getLocation();
        Rewrite.ReplaceText(loc, td->getUnderlyingType().getAsString());

        // now remove the identifier name from the end;
        loc = td->getUnderlyingDecl()->getEndLoc();
				Rewrite.ReplaceText(loc, "");
      }
    }
    if (const DeclStmt *ds =
            Result.Nodes.getNodeAs<clang::DeclStmt>("declstmt")) {
      // Assumption: The CFG has one DeclStmt per Decl.
      const VarDecl *vd = dyn_cast_or_null<VarDecl>(*ds->decl_begin());
      std::string canonicaltype;
      if (vd != NULL) {
        // first check if the type contains int float struct etc.
        auto type = vd->getType().getAsString();
				//cout<<vd->getNameAsString()<<" "<<type<<"\n";
        if (type.find("int") == std::string::npos &&
            type.find("float") == std::string::npos &&
            type.find("struct") == std::string::npos) {
          canonicaltype = vd->getType().getCanonicalType().getAsString();
					//cout<<vd->getNameAsString()<<" "<<canonicaltype<<"\n";
        // Replace the first of declsmt token with the canonical type;
        if(canonicaltype.find('[') != std::string::npos){
					canonicaltype = canonicaltype.substr(0, canonicaltype.find('['));	
				}
					Rewrite.ReplaceText(ds->getBeginLoc(), canonicaltype);
				}
      }
    }
  }
  Rewriter &Rewrite;
};
//-------------------------------------------------------------------------------------------------------------------------//
class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R) : typedefRenamer(R) {
    Finder.addMatcher(typedefDecl(isExpansionInMainFile()).bind("typedef"),
                      &typedefRenamer);
    Finder.addMatcher(
        declStmt(isExpansionInMainFile()).bind("declstmt"),
        &typedefRenamer);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    Finder.matchAST(Context);
  }

private:
  TypedefRenamer typedefRenamer;
  MatchFinder Finder;
};

//------------------------------------------------------------------------------------------------------------
//----------//
class MyFrontendAction : public ASTFrontendAction {
public:
  MyFrontendAction() {}
  Rewriter TheRewriter;

  void EndSourceFileAction() override {
    this->TheRewriter
        .getEditBuffer(this->TheRewriter.getSourceMgr().getMainFileID())
        .write(llvm::outs());
  }
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &Compiler,
                    llvm::StringRef InFile) override {
    this->TheRewriter.setSourceMgr(Compiler.getSourceManager(),
                                   Compiler.getLangOpts());
    PrintingPolicy printingPolicy(Compiler.getLangOpts());
    return std::unique_ptr<clang::ASTConsumer>(
        new MyASTConsumer(this->TheRewriter));
  }
};

//------------------------------------------------------------------------main
// starts--------------------------------//

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
  return 0;
}
