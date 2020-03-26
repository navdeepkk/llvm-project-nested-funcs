#include "/home/navdeep/work/projects/llvm-install/include/clang/AST/AST.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/AST/ASTContext.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/ASTMatchers/ASTMatchFinder.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/ASTMatchers/ASTMatchers.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Basic/SourceManager.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Basic/TokenKinds.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Frontend/CompilerInstance.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Frontend/FrontendActions.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Lex/Lexer.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Rewrite/Core/Rewriter.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Tooling/CommonOptionsParser.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Tooling/Refactoring.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Tooling/Tooling.h"
#include "/home/navdeep/work/projects/llvm-install/include/llvm/Support/CommandLine.h"
#include "/home/navdeep/work/projects/llvm-install/include/llvm/Support/raw_ostream.h"
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
    SourceManager *sm = Result.SourceManager;
    if (const LabelStmt *ls =
				Result.Nodes.getNodeAs<clang::LabelStmt>("label")) {
				Rewrite.InsertText(ls->getBeginLoc(), "\n");
				auto loc = ls->getBeginLoc();
				while (1) {
					if (std::strcmp(clang::Lexer::findNextToken(
															loc, Rewrite.getSourceMgr(),
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
		}
  }
  Rewriter &Rewrite;
};
//-------------------------------------------------------------------------------------------------------------------------//
class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R)
      : labelBuilder(R) {
    Finder.addMatcher(labelStmt().bind("label"), &labelBuilder);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    Finder.matchAST(Context);
  }

private:
  LabelFinder labelBuilder;
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
