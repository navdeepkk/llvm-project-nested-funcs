#include "/home/navdeep/work/projects/llvm-install/include/clang/AST/AST.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/AST/ASTContext.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/ASTMatchers/ASTMatchFinder.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/ASTMatchers/ASTMatchers.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Basic/SourceManager.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Frontend/CompilerInstance.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Frontend/FrontendActions.h"
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
//----------------------------------------------------global
// decls----------------------------------------------//
struct GlobalVars {
  std::string name;
  std::string type;
};

struct scope {
  std::string name;
  std::unordered_map<std::string, std::string> vars;
};

std::vector<GlobalVars> globalVars;
std::vector<std::string> labels;
std::unordered_map<std::string, std::string> parenChilMap;
std::unordered_map<std::string, scope> scopes;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp("\nMore help text...\n");

std::unordered_map<std::string, std::string> sourceLocs;
std::unordered_map<std::string, int> callDepths;

std::vector<std::pair<std::string, int>> depthSorted;

DeclarationMatcher globalMatcher =
    varDecl(hasDeclContext(translationUnitDecl())).bind("global");
StatementMatcher labelMatcher = labelStmt().bind("label");
std::unordered_map<std::string, int> depths;
std::stringstream ss;
std::stringstream ss2;
//------------------------------------------------/global decls
// end-------------------------------------------//

//------------------------------------------------------logic to convert the
// label depths into a sorted list depthsorted.
typedef std::function<bool(std::pair<std::string, int>,
                           std::pair<std::string, int>)>
    Comparator;
Comparator compFunctor = [](std::pair<std::string, int> elem1,
                            std::pair<std::string, int> elem2) {
  return elem1.second < elem2.second;
};
//-----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------classes and
// functions begin---------------------//
void structDump() {
  // building the structs of scope in order of depth.
  for (auto label : depthSorted) {
    ss << "struct s_" << label.first << " {\n"
       << "struct s_" << parenChilMap[label.first] << " * s;\n";
    for (auto var : scopes[label.first].vars) {
      // currently not adding any functionality to handle or structs any
      // differently.
      if (var.second.find('[') != std::string::npos) {
        ss << var.second.substr(0, var.second.find(' ')) << "* " << var.first
           << ":\n";
      } else {
        ss << var.second << "* " << var.first << ";\n";
        ;
      }
    }
    ss << "};\n\n";
  }
}
//-------------------------------------------------------------------------------------------------------------//
class GlobalBuilder : public MatchFinder::MatchCallback {
public:
  GlobalBuilder(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  GlobalVars temp;

  virtual void run(const MatchFinder::MatchResult &Result) {
    ASTContext *Context = Result.Context;
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("global")) {
      temp.type = vd->getType().getAsString();
      // llvm::errs()<<"globalbuilder\n";
      // llvm::errs()<<vd->getType().getAsString()<<"\n";
      temp.name = vd->getQualifiedNameAsString();
      globalVars.push_back(temp);
    }
  }
  Rewriter &Rewrite;
};
//---------------------------------------------------------------------------------------------------------------//
class LabelFinder : public MatchFinder::MatchCallback {
public:
  LabelFinder(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *sm = Result.SourceManager;
    if (const LabelStmt *ls =
            Result.Nodes.getNodeAs<clang::LabelStmt>("label")) {
      // llvm::errs()<<"labelfinder"<<ls->getName()<<"\n";
      labels.push_back(ls->getName());
      std::string loc = ls->getBeginLoc().printToString(*sm);
      loc = loc.substr(loc.find(':') + 1, loc.find(':'));
      loc = loc.substr(0, loc.find(':'));
      sourceLocs[ls->getName()] = loc;
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
      if (const LabelStmt *lp =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        // llvm::errs()<<"case1: \n";
        // llvm::errs()<<ls->getName()<<" "<<lp->getName();
        parenChilMap[ls->getName()] = lp->getName();
        depths[ls->getName()] = depths[lp->getName()] + 1;
      } else if (const FunctionDecl *fd =
                     Result.Nodes.getNodeAs<clang::FunctionDecl>("parent")) {
        // llvm::errs()<<"case2: \n";
        // llvm::errs()<<ls->getName()<<" "<<fd->getNameAsString();
        std::string loc = fd->getBeginLoc().printToString(*sm);
        loc = loc.substr(loc.find(':') + 1, loc.find(':'));
        loc = loc.substr(0, loc.find(':'));
        sourceLocs[fd->getNameAsString()] = loc;
        // llvm::errs()<<loc<<"\n";
        parenChilMap[ls->getName()] = fd->getNameAsString();
        // assuming that the nodes are visited in order of depth. starting from
        // lowest depth.
        depths[ls->getName()] = 1;
      }
    }
  }
  Rewriter &Rewrite;
};
//-------------------------------------------------------------------------------------------------------------------------//
class StructBuilder : public MatchFinder::MatchCallback {
public:
  StructBuilder(Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("child")) {
      // llvm::errs()<<"structBuilder\n";
      // find the appropriate parent child pair to insert it in. itereate
      // through parenChilMap and check if the source loc of the vardecl is in
      // between of parent and child.
      std::string loc = vd->getBeginLoc().printToString(*sm);
      // llvm::errs()<<loc<<"\n";
      loc = loc.substr(loc.find(':') + 1, loc.find(':'));
      loc = loc.substr(0, loc.find(':'));
      int varloc = std::stoi(loc);
      for (auto elem : parenChilMap) {
        // llvm::errs()<<sourceLocs[elem.first]<<"
        // "<<sourceLocs[elem.second]<<"\n";
        if (std::stoi(sourceLocs[elem.first]) >= varloc &&
            varloc >= std::stoi(sourceLocs[elem.second])) {
          // llvm::errs()<<"inserting in:"<<elem.first<<"\n";
          scopes[elem.first].name = elem.first;
          scopes[elem.first].vars[vd->getQualifiedNameAsString()] =
              vd->getType().getAsString();
        }
      }
    }
  }
  Rewriter &Rewrite;
};
//---------------------------------------------------------------------------------------------------------------------------//
class StructDumper : public MatchFinder::MatchCallback {
public:
  StructDumper(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *fd =
            Result.Nodes.getNodeAs<clang::FunctionDecl>("main")) {
      sourceLoc = fd->getBeginLoc();
    }
  }
  virtual void onEndOfTranslationUnit() {
    depthSorted =
        std::vector<std::pair<std::string, int>>(depths.begin(), depths.end());
    std::sort(depthSorted.begin(), depthSorted.end(), compFunctor);
    structDump();
    // llvm:errs()<<ss.str();
    Rewrite.InsertText(sourceLoc, ss.str(), true, true);
  }

private:
  Rewriter &Rewrite;
  SourceLocation sourceLoc;
};
//-----------------------------------------------------------------------------------------------------------------------//

class CallDepth : public MatchFinder::MatchCallback {
public:
  CallDepth() {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const CallExpr *ce =
            Result.Nodes.getNodeAs<clang::CallExpr>("depth1")) {
      std::string callName =
          ce->getDirectCallee()->getNameInfo().getName().getAsString();
      if (std::find(labels.begin(), labels.end(), callName) != labels.end()) {
        std::string loc = ce->getBeginLoc().printToString(*sm);
        loc = loc.substr(loc.find(':') + 1, loc.find(':'));
        loc = loc.substr(0, loc.find(':'));
        callDepths[callName + loc] = 1;
      }
    } else if (const CallExpr *ce =
                   Result.Nodes.getNodeAs<clang::CallExpr>("depth")) {
      std::string callName =
          ce->getDirectCallee()->getNameInfo().getName().getAsString();
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        if (std::find(labels.begin(), labels.end(), callName) != labels.end()) {
          std::string callName =
              ce->getDirectCallee()->getNameInfo().getName().getAsString();
          std::string loc = ce->getBeginLoc().printToString(*sm);
          loc = loc.substr(loc.find(':') + 1, loc.find(':'));
          loc = loc.substr(0, loc.find(':'));
          callDepths[callName + loc] = depths[ls->getName()] + 1;
        }
      }
    }
  }
};
//--------------------------------------------------------------------------------------------------------------------------//

class StructInit : public MatchFinder::MatchCallback {
public:
  StructInit(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const CallExpr *ce = Result.Nodes.getNodeAs<clang::CallExpr>("call")) {
      std::string callName =
          ce->getDirectCallee()->getNameInfo().getName().getAsString();
      if (std::find(labels.begin(), labels.end(), callName) != labels.end()) {

        std::string loc = ce->getBeginLoc().printToString(*sm);
        loc = loc.substr(loc.find(':') + 1, loc.find(':'));
        loc = loc.substr(0, loc.find(':'));
        if (callDepths[callName + loc] == depths[callName]) {
          sourceLoc = ce->getBeginLoc();
          ss2 << "struct s_" << callName << " s" << callName << ";\n";
          for (auto var : scopes[callName].vars) {
            // llvm::errs() << var.first << " " << var.second << " \n";
            ss2 << "s" << callName << "." << var.first << " =  &" << var.first
                << ";\n";
          }
          // llvm::errs() << ss2.str() << "\n";
          Rewrite.InsertText(sourceLoc, ss2.str(), true, true);
        }
      }
    }
    ss2.clear();
  }

private:
  Rewriter &Rewrite;
  SourceLocation sourceLoc;
};

//--------------------------------------------------------------------------------------------------------------------------//

class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R)
      : globalBuilder(R), structDumper(R), labelRelBuilder(R), labelBuilder(R),
        structBuilder(R), callDepth(), structInit(R) {
    // all code from main goes here.
    // Find all the globals and labelStmt first.
    // Find all the globals and store them in struct with type and identfier.
    Finder.addMatcher(globalMatcher, &globalBuilder);
    // find all the labelStmt and store there name in a vector of strings.
    Finder.addMatcher(labelMatcher, &labelBuilder);
    // below matcher returns all node at depth level one.
    Finder.addMatcher(labelStmt(hasParent(compoundStmt(
                                    hasParent(functionDecl().bind("parent")))))
                          .bind("child"),
                      &labelRelBuilder);
    // find the parent child relationship of label statements by matching all
    // nodes having a compound statement as parent;
    Finder.addMatcher(
        labelStmt(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &labelRelBuilder);
    // for all nodes find the variables that need to be passed on into its
    // scope.
    //  Finder.addMatcher(labelStmt(hasParent(compoundStmt().bind("parent"))).bind("child"),
    //  &structBuilder);
    // for all nodes find the variables that need to be passed on into its
    // scope.
    DelayedFinder.addMatcher(
        varDecl(hasAncestor(functionDecl(hasName("main")))).bind("child"),
        &structBuilder);
    // after this call the depths will be sorted. structBuilder has a logicc to
    // sort the depths. adding code to find the main function and rewrite
    // something there.
    DelayedFinder.addMatcher(functionDecl(hasName("main")).bind("main"),
                             &structDumper);
    // Next thing would be to find the depths of the call expressions, so
    // appropriate redirections for variables may be provided. first finding all
    // call at depth one.
    DelayedFinder.addMatcher(callExpr(hasParent(compoundStmt(hasParent(
                                          functionDecl(hasName("main"))))))
                                 .bind("depth1"),
                             &callDepth);
    // finding the call expressions at more depths
    DelayedFinder.addMatcher(
        callExpr(hasAncestor(labelStmt().bind("parent"))).bind("depth"),
        &callDepth);
    // now the depths are in hand the logic to initialize scope srtuctures
    // before function calls must start.
    DelayedFinder.addMatcher(
        callExpr(hasAncestor(labelStmt().bind("parent"))).bind("call"),
        &structInit);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    // Run the matchers when we have the whole TU parsed.
    Finder.matchAST(Context);
    /*
        for (auto loc : sourceLocs){
            llvm::errs()<<loc.first<<" "<<loc.second<<"\n";
       }
        for (auto depth : depths ){
            llvm::errs() << depth.first<<" "<<depth.second<<"\n";
      }
    */
    DelayedFinder.matchAST(Context);

    //  for(auto depths: callDepths){
    //    llvm::errs()<<depths.first<<" "<<depths.second<<"\n";
    /// }
  }

private:
  GlobalBuilder globalBuilder;
  LabelFinder labelBuilder;
  LabelRelBuilder labelRelBuilder;
  StructBuilder structBuilder;
  StructDumper structDumper;
  CallDepth callDepth;
  StructInit structInit;
  MatchFinder Finder;
  MatchFinder DelayedFinder;
};
//----------------------------------------------------------------------------------------------------------------------//
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
  CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    this->TheRewriter.setSourceMgr(Compiler.getSourceManager(),
                                   Compiler.getLangOpts());
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
