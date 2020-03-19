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
struct GlobalVars {
  std::string name;
  std::string type;
};

struct scope {
  std::string name;
  std::unordered_map<std::string, std::string> vars;
  std::unordered_map<std::string, int> locs;
};

struct bounds {
  int begin;
  int end;
};

std::vector<GlobalVars> globalVars;
std::vector<std::string> globalFuncDecls;
std::vector<std::string> labels;
std::unordered_map<std::string, std::string> parenChilMap;
// scopes is for the scopes that need to be passed on into the functions.
std::unordered_map<std::string, scope> scopes;
// decls is for the decalrations that are inside a function or label stmt.
std::unordered_map<std::string, scope> decls;
// call rels is for resolution of calls to appropriate funcitons or labels.
std::unordered_map<std::string, std::string> callRels;
// visited labels is for the contructions of decls. marks the parent label stmts
// visited. in a new matcher this visited labels would not be considered.
std::unordered_map<std::string, bool> visitedLabels;
// labelbounds has label bounds.
std::unordered_map<std::string, bounds> labelBounds;
// rewrttien bodies haves the bodies in the form of string of respective label
// stmt.
std::unordered_map<std::string, std::string> rewrittenBodies;
std::unordered_map<std::string, std::string> rewrittenBodiesFin;

std::unordered_map<std::string, std::string> sourceLocs;
std::unordered_map<std::string, int> callDepths;

std::vector<std::pair<std::string, int>> depthSorted;
std::unordered_map<std::string, bool> structMade;
// marked call depths is utility for finding call depths, marks all the calls as
// true. so they are not processed again.
std::unordered_map<std::string, bool> resolvedCalls;
DeclarationMatcher globalMatcher =
    varDecl(hasDeclContext(translationUnitDecl())).bind("global");
StatementMatcher labelMatcher = labelStmt().bind("label");
std::unordered_map<std::string, int> depths;
std::unordered_map<std::string, int> vardecldepths;
std::stringstream ss;
std::stringstream ss2;
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
      // llvm::errs()<<"labelfinder"<<ls->getName()<<"\n";
      std::string loc = ls->getBeginLoc().printToString(*sm);
      loc = loc.substr(loc.find(':') + 1, loc.find(':'));
      loc = loc.substr(0, loc.find(':'));
      sourceLocs[ls->getName() + loc] = loc;
      labels.push_back(ls->getName() + loc);
      // initialize as !visitedLabels[lsName + lsloc] as false.
      visitedLabels[ls->getName() + loc] = false;
      // llvm::errs()<<loc<<"\n";
    }
  }
  Rewriter &Rewrite;
};
//--------------------------------------------------------------------------------------------------------------------//
class LabelRelBuilder : public MatchFinder::MatchCallback {
public:
  LabelRelBuilder(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *sm = Result.SourceManager;
    if (const LabelStmt *ls =
            Result.Nodes.getNodeAs<clang::LabelStmt>("child")) {
      // find source loc of child
      std::string locls = ls->getBeginLoc().printToString(*sm);
      locls = locls.substr(locls.find(':') + 1, locls.find(':'));
      locls = locls.substr(0, locls.find(':'));
      // add the source loc of child into sourceLocs.
      sourceLocs[ls->getName() + locls] = locls;
      // if parent is a labelstmt.
      if (const LabelStmt *lp =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        // find source loc of parent.
        std::string loclp = lp->getBeginLoc().printToString(*sm);
        loclp = loclp.substr(loclp.find(':') + 1, loclp.find(':'));
        loclp = loclp.substr(0, loclp.find(':'));
        sourceLocs[lp->getName() + loclp] = loclp;
        parenChilMap[ls->getName() + locls] = lp->getName() + loclp;
        depths[ls->getName() + locls] = depths[lp->getName() + loclp] + 1;
        // if parent is a function decl.
      } else if (const FunctionDecl *fd =
                     Result.Nodes.getNodeAs<clang::FunctionDecl>("parent")) {
        std::string loclp = fd->getBeginLoc().printToString(*sm);
        loclp = loclp.substr(loclp.find(':') + 1, loclp.find(':'));
        loclp = loclp.substr(0, loclp.find(':'));
        sourceLocs[fd->getNameAsString() + loclp] = loclp;
        parenChilMap[ls->getName() + locls] = fd->getNameAsString() + loclp;
        // assuming that the nodes are visited in order of depth. starting from
        // lowest depth.
        depths[ls->getName() + locls] = 1;
        depths[fd->getNameAsString() + loclp] = 0;
      }
    }
  }
  Rewriter &Rewrite;
};
//------------------------------------------------------------------------------------------------------------//
class LabelRenamer : public MatchFinder::MatchCallback {
public:
  LabelRenamer(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const LabelStmt *ls =
            Result.Nodes.getNodeAs<clang::LabelStmt>("stmt")) {
      std::string lsname = ls->getName();
      std::string locls = ls->getBeginLoc().printToString(*sm);
      locls = locls.substr(locls.find(':') + 1, locls.find(':'));
      locls = locls.substr(0, locls.find(':'));
      Rewrite.ReplaceText(ls->getBeginLoc(), lsname + "( struct s_" +
                                                 lsname+ "* __s )");
    }
  }

private:
  Rewriter &Rewrite;
};
//------------------------------------------------------------------------------------------------------------//
class LabelRemover : public MatchFinder::MatchCallback {
public:
  LabelRemover(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const LabelStmt *ls =
            Result.Nodes.getNodeAs<clang::LabelStmt>("stmt")) {
      std::string lsname = ls->getName();
      std::string locls = ls->getBeginLoc().printToString(*sm);
      locls = locls.substr(locls.find(':') + 1, locls.find(':'));
      locls = locls.substr(0, locls.find(':'));
      if (depths[lsname + locls] == 1) {
        Rewrite.ReplaceText(ls->getSourceRange(), "\n");
      }
    }
  }

private:
  Rewriter &Rewrite;
};
//-------------------------------------------------------------------------------------------------------------------------//
class LabelHoist : public MatchFinder::MatchCallback {
public:
  LabelHoist(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *sm = Result.SourceManager;
    if (const LabelStmt *ls =
            Result.Nodes.getNodeAs<clang::LabelStmt>("child")) {
      // find source loc of child
      std::string locls = ls->getBeginLoc().printToString(*sm);
      locls = locls.substr(locls.find(':') + 1, locls.find(':'));
      locls = locls.substr(0, locls.find(':'));
      // if parent is a labelstmt.
      if (const LabelStmt *lp =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        // find source loc of parent.
        std::string loclp = lp->getBeginLoc().printToString(*sm);
        loclp = loclp.substr(loclp.find(':') + 1, loclp.find(':'));
        loclp = loclp.substr(0, loclp.find(':'));
        // insert the rewritten body of the child label stmt into a
        // map hashed by the name and loc of the child labelstmt.
        rewrittenBodies[ls->getName() + locls] =
            Rewrite.getRewrittenText(ls->getSourceRange());
        rewrittenBodiesFin[ls->getName() + locls] =
            Rewrite.getRewrittenText(ls->getSourceRange());
        // cout << Rewrite.getRewrittenText(ls->getSourceRange()) << "\n";
        // if parent is a function decl.
      } else if (const FunctionDecl *fd =
                     Result.Nodes.getNodeAs<clang::FunctionDecl>("parent")) {
        std::string loclp = fd->getBeginLoc().printToString(*sm);
        loclp = loclp.substr(loclp.find(':') + 1, loclp.find(':'));
        loclp = loclp.substr(0, loclp.find(':'));
        // insert the rewritten body of the child label stmt into a
        // map hashed by the name and loc of the child labelstmt.
        rewrittenBodies[ls->getName() + locls] =
            Rewrite.getRewrittenText(ls->getSourceRange());
        rewrittenBodiesFin[ls->getName() + locls] =
            Rewrite.getRewrittenText(ls->getSourceRange());
        // cout << Rewrite.getRewrittenText(ls->getSourceRange()) << "\n";
      }
    }
  }
  Rewriter &Rewrite;
};
//---------------------------------------------------------------------------------------------------------------------------//
class FunctionDumper : public MatchFinder::MatchCallback {
public:
  FunctionDumper(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const TranslationUnitDecl *tu =
            Result.Nodes.getNodeAs<clang::TranslationUnitDecl>("main")) {
      sourceLoc = tu->getASTContext().getSourceManager().getLocForEndOfFile(
          tu->getASTContext().getSourceManager().getMainFileID());
    }
  }
  virtual void onEndOfTranslationUnit() {
    stringstream ss;
    ss << "\n\n";
    for (auto label : labels) {
			ss<<"void ";
      ss << rewrittenBodiesFin[label] << "\n\n";
    }
    Rewrite.InsertTextBefore(sourceLoc, ss.str());
  }

private:
  Rewriter &Rewrite;
  SourceLocation sourceLoc;
};
//-------------------------------------------------------------------------------------------------------------------------//
class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R)
      : labelRemover(R), labelBuilder(R), labelRelBuilder(R), labelRenamer(R),
        labelHoist(R), functionDumper(R) {
    Finder.addMatcher(labelMatcher, &labelBuilder);
    Finder.addMatcher(
        labelStmt(hasAncestor(functionDecl().bind("parent"))).bind("child"),
        &labelRelBuilder);
    // find the parent child relationship of label statements by matching all
    // nodes having a compound statement as parent;
    Finder.addMatcher(
        labelStmt(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &labelRelBuilder);
    // renmae label statements.
    LabelRenameFinder.addMatcher(labelStmt().bind("stmt"), &labelRenamer);
    // label hoisting begins
    LabelHoistFinder.addMatcher(
        labelStmt(hasAncestor(functionDecl().bind("parent"))).bind("child"),
        &labelHoist);
    LabelHoistFinder.addMatcher(
        labelStmt(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &labelHoist);
    // remove label stmts from the code.
    LabelRemoveFinder.addMatcher(labelStmt().bind("stmt"), &labelRemover);
    FunctionDumpFinder.addMatcher(translationUnitDecl().bind("main"),
                                  &functionDumper);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    Finder.matchAST(Context);
    LabelRenameFinder.matchAST(Context);
		LabelHoistFinder.matchAST(Context);
    //-----------------------------------------now we can trim down the strings
    // in random order.
    for (auto label : labels) {
      for (auto elem : parenChilMap) {
        if (label == elem.second) {
          // match found, do trimming of strings.
          size_t pos =
              rewrittenBodiesFin[elem.second].find(rewrittenBodies[elem.first]);
          rewrittenBodiesFin[label].erase(pos,
                                          rewrittenBodies[elem.first].length());
        }
      }
    }
    // now the trimming of the strings has been done then we can go on to modify
    // teh strings to chang the starting of the labels to be as of that a
    // funtion. removing colon form the body of the functions.
    for (auto label : labels) {
      size_t pos = rewrittenBodiesFin[label].find(":");
      rewrittenBodiesFin[label].erase(pos, 1);
    }

    LabelRemoveFinder.matchAST(Context);
    FunctionDumpFinder.matchAST(Context);
  }

private:
  LabelFinder labelBuilder;
  LabelRelBuilder labelRelBuilder;
  LabelRenamer labelRenamer;
  LabelHoist labelHoist;
  LabelRemover labelRemover;
  FunctionDumper functionDumper;
  MatchFinder Finder;
  MatchFinder MainDumpFinder;
  MatchFinder DelayedFinder;
  MatchFinder DelayedFinder2;
  MatchFinder DelayedFinder3;
  MatchFinder MatchCallResolver;
  MatchFinder MatchCallResolver2;
  MatchFinder LastLabelFinder;
  MatchFinder VarDepthFinder;
  MatchFinder RewriteFinder;
  MatchFinder LabelRenameFinder;
  MatchFinder LabelHoistFinder;
  MatchFinder LabelRemoveFinder;
  MatchFinder FunctionDumpFinder;
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
