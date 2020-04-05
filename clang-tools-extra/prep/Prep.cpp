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
class LabelFinder : public MatchFinder::MatchCallback {
public:
  LabelFinder(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const LabelStmt *ls =
            Result.Nodes.getNodeAs<clang::LabelStmt>("label")) {
      Rewrite.InsertText(ls->getBeginLoc(), "\n");
      auto loc = ls->getBeginLoc();
      while (1) {
        if (std::strcmp(clang::Lexer::findNextToken(loc, Rewrite.getSourceMgr(),
                                                    Rewrite.getLangOpts())
                            ->getName(),
                        "l_brace") == 0) {
          break;
        }
        loc = clang::Lexer::findNextToken(loc, Rewrite.getSourceMgr(),
                                          Rewrite.getLangOpts())
                  ->getLocation();
      }
      loc = clang::Lexer::findNextToken(loc, Rewrite.getSourceMgr(),
                                        Rewrite.getLangOpts())
                ->getLocation();

      Rewrite.InsertTextAfterToken(loc, "\n");
    } else if (const RecordDecl *ls =
                   Result.Nodes.getNodeAs<clang::RecordDecl>("record")) {
      Rewrite.InsertText(ls->getBeginLoc(), "\n");
      auto loc = ls->getBeginLoc();
      while (1) {
        if (std::strcmp(clang::Lexer::findNextToken(loc, Rewrite.getSourceMgr(),
                                                    Rewrite.getLangOpts())
                            ->getName(),
                        "l_brace") == 0) {
          break;
        }
        loc = clang::Lexer::findNextToken(loc, Rewrite.getSourceMgr(),
                                          Rewrite.getLangOpts())
                  ->getLocation();
      }
      loc = clang::Lexer::findNextToken(loc, Rewrite.getSourceMgr(),
                                        Rewrite.getLangOpts())
                ->getLocation();

      Rewrite.InsertTextAfterToken(loc, "\n");
    } else if (const DeclStmt *ds =
                   Result.Nodes.getNodeAs<clang::DeclStmt>("decl")) {
      bool flag = false;
      std::stringstream buff;
      // iterate through all the children and find if record decl is present
      // then vardecl of the type record decl is present.
      for (auto decl = ds->decl_begin(); decl < ds->decl_end(); decl++) {
        if (const RecordDecl *rd = dyn_cast_or_null<RecordDecl>(*decl)) {
					buff<<Rewrite.getRewrittenText(rd->getSourceRange())<<";";
					flag = true;
        }
      }
      if (flag) {
        // not sure in what order the children are visited so visitng once
        // again.
        for (auto decl = ds->decl_begin(); decl < ds->decl_end(); decl++) {	
          if (const VarDecl *vd = dyn_cast_or_null<VarDecl>(*decl)) {
            //Rewrite.ReplaceText(vd->getEndLoc(), "");
            // remove the following ',', removes';' also.
            //Rewrite.ReplaceText(
            //    clang::Lexer::findNextToken(vd->Decl::getEndLoc(),
            //                                Rewrite.getSourceMgr(),
            //                                Rewrite.getLangOpts())
            //        ->getLocation(),
            //    "");
            // convert into a definition of a stuct and insert this into buff
            // to print it at the end of the decl stmt.
            auto type = vd->getType().getAsString();
            if (type.find("struct") == 0) {
              // if it is not of array type then just insert the var name
              // after the end of the type.
              if (type.find('[') == std::string::npos) {
                type.append(" ");
                type.append(vd->getNameAsString());
                buff << "\n" << type << ";\n";
              } else {
                type.insert(type.find('['), vd->getNameAsString());
                buff << "\n" << type << ";\n";
              }
            }
          }
        }
				//insert buff at end of the decl stmt;
				if(!buff.str().empty()){
					//removing the decl stmt.
					Rewrite.ReplaceText(ds->getSourceRange(),buff.str());	
					/*
            Rewrite.ReplaceText(
                clang::Lexer::findNextToken(ds->getEndLoc(),
                                            Rewrite.getSourceMgr(),
                                            Rewrite.getLangOpts())
                    ->getLocation(),
                buff.str());
					*/
					//Rewrite.InsertTextAfter(decendloc, buff.str());
				}
				buff.str("");
      }
    }
  }
  Rewriter &Rewrite;
};
//-------------------------------------------------------------------------------------------------------------------------//
class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R) : labelBuilder(R) {
    Finder.addMatcher(labelStmt(isExpansionInMainFile()).bind("label"),
                      &labelBuilder);
    Finder.addMatcher(recordDecl(isExpansionInMainFile()).bind("record"),
                      &labelBuilder);
    Finder2.addMatcher(declStmt(isExpansionInMainFile()).bind("decl"),
                       &labelBuilder);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    Finder.matchAST(Context);
    Finder2.matchAST(Context);	
  }

private:
  LabelFinder labelBuilder;
  MatchFinder Finder;
  MatchFinder Finder2;
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
