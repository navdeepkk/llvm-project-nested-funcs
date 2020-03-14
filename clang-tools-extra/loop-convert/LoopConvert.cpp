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
static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp("\nMore help text...\n");

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
    // run only for those functions whose depth is not zero and also
    // parenchilmap is not empty
    if (label.second != 0 && !parenChilMap[label.first].empty()) {
      ss << "struct s_" << label.first << " {\n";
      // add only if the depth of the parent is grater than 0.
      if (depths[parenChilMap[label.first]] != 0) {
        ss << "struct s_" << parenChilMap[label.first] << " *s;\n";
      }
      for (auto var : scopes[label.first].vars) {
        // currently not adding any functionality to handle or structs any
        // differently.
        if (var.second.find('[') != std::string::npos) {
          ss << var.second.substr(0, var.second.find(' ')) << "* " << var.first
             << ";\n";
        } else {
          ss << var.second << "* " << var.first << ";\n";
          ;
        }
      }
      ss << "};\n\n";
    }
  }
}
//-------------------------------------------------------------------------------------------------------------//
class GlobalBuilder : public MatchFinder::MatchCallback {
public:
  GlobalBuilder(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  GlobalVars temp;

  virtual void run(const MatchFinder::MatchResult &Result) {
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
//-------------------------------------------------------------------------------------------------------------------------//
class StructBuilder : public MatchFinder::MatchCallback {
public:
  StructBuilder(Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("child")) {
      // find the appropriate parent child pair to insert it in. itereate
      // through parenChilMap and check if the source loc of the vardecl is in
      // between of parent and child.
      std::string loc = vd->getBeginLoc().printToString(*sm);
      if (loc.find("invalid") == std::string::npos) {
        loc = loc.substr(loc.find(':') + 1, loc.find(':'));
        loc = loc.substr(0, loc.find(':'));
        int varloc = std::stoi(loc);
        for (auto elem : parenChilMap) {
          if (std::stoi(sourceLocs[elem.first]) > varloc &&
              varloc >= std::stoi(sourceLocs[elem.second])) {
            // inserting into scopes for child label stmt
            // with name stype and scope.
            scopes[elem.first].name = elem.first;
            scopes[elem.first].vars[vd->getQualifiedNameAsString()] =
                vd->getType().getAsString();
            scopes[elem.first].locs[vd->getQualifiedNameAsString()] = varloc;
            visitedLabels[elem.second] = true;
          }
        }
      }
    }
  }
  Rewriter &Rewrite;
};
//------------------------------------------------------------------------find
// depths of all vardecl inside label statements------------//////

class VarDepthFinder : public MatchFinder::MatchCallback {
public:
  VarDepthFinder() {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    // initialize depths of all var decls as one.
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("one")) {
      std::string vdName = vd->getNameAsString();
      // llvm::errs()<<vdName<<"\n";
      std::string vdloc = vd->getBeginLoc().printToString(*sm);
      // llvm::errs() << vdloc << "\n";
      vdloc = vdloc.substr(vdloc.find(':') + 1, vdloc.find(':'));
      vdloc = vdloc.substr(0, vdloc.find(':'));
      // llvm::errs()<<vdloc<<"\n";
      if (vdloc.find("invalid") == std::string::npos) {
        vardecldepths[vdName + vdloc] = 1;
      }
    }
    // handle vardecs in label stmts.
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("child")) {
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        std::string lsName = ls->getName();
        std::string lsloc = ls->getBeginLoc().printToString(*sm);
        lsloc = lsloc.substr(lsloc.find(':') + 1, lsloc.find(':'));
        lsloc = lsloc.substr(0, lsloc.find(':'));

        std::string vdName = vd->getNameAsString();
        std::string vdloc = vd->getBeginLoc().printToString(*sm);
        vdloc = vdloc.substr(vdloc.find(':') + 1, vdloc.find(':'));
        vdloc = vdloc.substr(0, vdloc.find(':'));
        if (vdloc.find("invalid") == std::string::npos) {
          vardecldepths[vdName + vdloc] = depths[lsName + lsloc] + 1;
        }
      }
    }
    // handle vardecls at global level.
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("child")) {
      if (const TranslationUnitDecl *tu =
              Result.Nodes.getNodeAs<clang::TranslationUnitDecl>("parent")) {

        std::string vdName = vd->getNameAsString();
        // llvm::errs()<<vdName<<"\n";
        std::string vdloc = vd->getSourceRange().getBegin().printToString(*sm);
        // llvm::errs()<<vdloc<<"\n";
        vdloc = vdloc.substr(vdloc.find(':') + 1, vdloc.find(':'));
        vdloc = vdloc.substr(0, vdloc.find(':'));
        if (vdloc.find("invalid") == std::string::npos) {
          vardecldepths[vdName + vdloc] = 0;
        }
      }
    }
  }
};
//---------------------------------------------------------------------------------------------------------------------//

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
    Rewrite.InsertTextBefore(sourceLoc, ss.str());
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
      // llvm::errs() << "callee: " << callName << "\n";
      // find the source loc to find ce + sourceloc in labels vector.
      std::string loc = ce->getBeginLoc().printToString(*sm);
      loc = loc.substr(loc.find(':') + 1, loc.find(':'));
      loc = loc.substr(0, loc.find(':'));
      callDepths[callName + loc] = 1;
    } else if (const CallExpr *ce =
                   Result.Nodes.getNodeAs<clang::CallExpr>("depth")) {
      std::string callName =
          ce->getDirectCallee()->getNameInfo().getName().getAsString();
      // find source loc of call expr to find ce + sourceloc in labels vector.
      std::string loc = ce->getBeginLoc().printToString(*sm);
      loc = loc.substr(loc.find(':') + 1, loc.find(':'));
      loc = loc.substr(0, loc.find(':'));
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        // find the loc of parent label to hash into the depths list.
        std::string lsloc = ls->getBeginLoc().printToString(*sm);
        lsloc = lsloc.substr(lsloc.find(':') + 1, lsloc.find(':'));
        lsloc = lsloc.substr(0, lsloc.find(':'));
        callDepths[callName + loc] = depths[ls->getName() + lsloc] + 1;
      }
    }
  }
};
//--------------------------------------------------------------------------------------------------------------------//
class GlobalFuncDeclFinder : public MatchFinder::MatchCallback {
public:
  GlobalFuncDeclFinder() {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    // llvm::errs() << "global found.\n";
    SourceManager *const sm = Result.SourceManager;
    if (const FunctionDecl *fd =
            Result.Nodes.getNodeAs<clang::FunctionDecl>("decl")) {
      if (fd->isGlobal()) {
        globalFuncDecls.push_back(fd->getNameAsString());
      }
    }
  }
};
//----------------------------------------------------------------------------------------------------------------//
class CallResolver : public MatchFinder::MatchCallback {
public:
  CallResolver() {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const CallExpr *ce = Result.Nodes.getNodeAs<clang::CallExpr>("call")) {
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        std::string callName =
            ce->getDirectCallee()->getNameInfo().getName().getAsString();
        std::string lsName = ls->getName();
        // once labelstmt name is known traverse all the parents recursively to
        // see if any labelstmt has the same name
        // as the callexpr. if i find match then stop and the call is resolved
        // to that label else if you reach a fucntion with depth zero then go on
        // to check if a global function is present or not.
        std::string lsloc = ls->getBeginLoc().printToString(*sm);
        lsloc = lsloc.substr(lsloc.find(':') + 1, lsloc.find(':'));
        lsloc = lsloc.substr(0, lsloc.find(':'));
        //--------------------------find loc of call-------------------//
        std::string celoc = ce->getBeginLoc().printToString(*sm);
        celoc = celoc.substr(celoc.find(':') + 1, celoc.find(':'));
        celoc = celoc.substr(0, celoc.find(':'));
        // check if there is a labestmt or functiondecl with same name as the
        // call expr at the same depth.
        // llvm::errs() << "helllo from call resolver\n";
        if (resolvedCalls[callName + celoc] == false) {
          std::string res = findCall(lsName + lsloc, callName, celoc);
          // llvm::errs() << callName + celoc << " " << res << "\n";
          // if 0 is returned then 2 cases are possible either the call resolves
          // to a global thing or it resolves to a label stmt at same depth.
          if (res.compare("0") == 0) {
            // search in parenchilmap for the label stmt that encloses this call
            // expression. if the label stmt has an immediate label stmt with
            // the same name then the call will resolve to it.
            bool flag = false;
            for (auto elem : parenChilMap) {
              if (elem.second.compare(lsName + lsloc) == 0) {
                // the elem has the labelstmt as parent
                std::string temp = elem.first;
                // temp capture the name of child labelstmt;
                temp.erase(remove_if(temp.begin(), temp.end(),
                                     [](char c) { return !isalpha(c); }),
                           temp.end());
                if (temp.compare(callName) == 0) {
                  resolvedCalls[callName + celoc] = true;
                  callRels[callName + celoc] = elem.first;
                  // llvm::errs() << callName + celoc << " " << elem.first <<
                  // "\n";
                  break;
                }
              }
            }
          }
        }
      } else if (const FunctionDecl *fd =
                     Result.Nodes.getNodeAs<clang::FunctionDecl>("parent")) {
        // if call is not resolved here also then it should be checked for
        // global.
        std::string callName =
            ce->getDirectCallee()->getNameInfo().getName().getAsString();
        std::string celoc = ce->getBeginLoc().printToString(*sm);
        celoc = celoc.substr(celoc.find(':') + 1, celoc.find(':'));
        celoc = celoc.substr(0, celoc.find(':'));

        std::string fdName = fd->getQualifiedNameAsString();
        std::string fdloc = fd->getBeginLoc().printToString(*sm);
        fdloc = fdloc.substr(fdloc.find(':') + 1, fdloc.find(':'));
        fdloc = fdloc.substr(0, fdloc.find(':'));
        // have name for both fd and ce check if it is unvisited
        if (resolvedCalls[callName + celoc] == false) {
          std::string res = findCall(fdName + fdloc, callName, celoc);
          // llvm::errs() << callName + celoc << " " << res << "\n";
          // if 0 is returned then 2 cases are possible either the call resolves
          // to a global thing or it resolves to a label stmt at same depth.
          if (res.compare("0") == 0) {
            // search in parenchilmap for the label stmt that encloses this call
            // expression. if the label stmt has an immediate label stmt with
            // the same name then the call will resolve to it. else it will
            // resolve to a global function
            bool flag = false;
            for (auto elem : parenChilMap) {
              if (elem.second.compare(fdName + fdloc) == 0) {
                // the elem has the labelstmt as parent
                std::string temp = elem.first;
                // temp capture the name of child labelstmt;
                temp.erase(remove_if(temp.begin(), temp.end(),
                                     [](char c) { return !isalpha(c); }),
                           temp.end());
                if (temp.compare(callName) == 0) {
                  flag = true;
                  resolvedCalls[callName + celoc] = true;
                  callRels[callName + celoc] = elem.first;
                  // llvm::errs() << callName + celoc << " " << elem.first <<
                  // "\n";
                  break;
                }
              }
            }
            // if call is foudn anywhere then it resolves to the global call.
            if (!flag) {
              callRels[callName + celoc] = callName;
            }
          }
        }
      }
    }
  }

  std::string findCall(std::string ls, std::string target, std::string celoc) {
    std::string temp = ls;
    // removes digits from the name of the label.
    ls.erase(
        remove_if(ls.begin(), ls.end(), [](char c) { return !isalpha(c); }),
        ls.end());
    // check if there is matching label or functions decl at depth 1.
    /*
    std::string temp2;
    for (auto depth : depths) {
                        ///temp2 is for holding the target label name of the
    label to compare it with the name of the call, because depths has label
    namescombined with sourceloc. temp2 = depth.first;
      temp2.erase(remove_if(temp2.begin(), temp2.end(),
                            [](char c) { return !isalpha(c); }),
                  temp2.end());
      if (depth.second == callDepths[target + celoc] && temp2 == target) {
        return depth.first;
      }
    }*/
    if (depths[temp] == 0) {
      if (ls.compare(target) == 0) {
        // if label at depth 0 is same as call then return it.
        // call resolution successfull mark true.
        resolvedCalls[target + celoc] = true;
        callRels[target + celoc] = temp;
        return temp;
      } else {
        return "0";
      }
    }
    // check if the name of the label is same as the callee.
    if (ls.compare(target) == 0) {
      // call resolution is successfull mark true.
      resolvedCalls[target + celoc] = true;
      callRels[target + celoc] = temp;
      return temp;
    } else {
      return findCall(parenChilMap[temp], target, celoc);
    }
  }
};
//--------------------------------------------------------------------------------------------------------------------------//

class LabelLast : public MatchFinder::MatchCallback {
public:
  LabelLast() {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("child")) {
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        std::string lsName = ls->getName();
        std::string lsloc = ls->getBeginLoc().printToString(*sm);
        lsloc = lsloc.substr(lsloc.find(':') + 1, lsloc.find(':'));
        // findign the end label bounds
        std::string lsendloc = ls->getEndLoc().printToString(*sm);
        lsendloc = lsendloc.substr(lsendloc.find(':') + 1, lsendloc.find(':'));
        lsendloc = lsendloc.substr(0, lsendloc.find(':'));
        // inserting the label bounds into the labelBounds.
        // llvm::errs() << lsName << " " << lsloc << " " << lsendloc << "\n";
        labelBounds[lsName + lsloc].begin = std::stoi(lsloc);
        labelBounds[lsName + lsloc].end = std::stoi(lsendloc);

        // llvm::errs() << "hello from lastlabel\n";
        lsloc = lsloc.substr(0, lsloc.find(':'));
        //  if (!visitedLabels[lsName + lsloc]) {
        // llvm::errs() << "yes\n";
        std::string loc = vd->getBeginLoc().printToString(*sm);
        loc = loc.substr(loc.find(':') + 1, loc.find(':'));
        loc = loc.substr(0, loc.find(':'));
        int varloc = std::stoi(loc);
        // llvm::errs() << lsName + lsloc << " " <<
        // vd->getQualifiedNameAsString()
        //             << "\n";
        // inserting into decl for the parent label stmt . usefull when re
        // writing. not to rewrite the vars that are declared in the
        // function. second is the parent first is child. marking the parent
        // as true visited.
        decls[lsName + lsloc].name = lsName + lsloc;
        decls[lsName + lsloc].vars[vd->getQualifiedNameAsString()] =
            vd->getType().getAsString();
        decls[lsName + lsloc].locs[vd->getQualifiedNameAsString()] = varloc;
      }
    }
  }
};
//----------------------------------------------------------------------------------------------------------------------//
class StructInit : public MatchFinder::MatchCallback {
public:
  StructInit(Rewriter &Rewrite) : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const CallExpr *ce = Result.Nodes.getNodeAs<clang::CallExpr>("call")) {
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        // bind the call expr and its parent label stmt.
        std::string callName =
            ce->getDirectCallee()->getNameInfo().getName().getAsString();
        std::string callLoc = ce->getBeginLoc().printToString(*sm);
        callLoc = callLoc.substr(callLoc.find(':') + 1, callLoc.find(':'));
        callLoc = callLoc.substr(0, callLoc.find(':'));
        // rewrite only those calls which are to label stmt.
        // callrels can be used here.
        if (callRels.find(callName + callLoc) != callRels.end()) {
          // if multiple call in a label stmt then only one call is to be
          // preceded by a structure definition.
          if (structMade[ls->getName() + callName] == false) {
            llvm::errs() << "entered init;\n";
            // if the call is of a label stmt and a struct for it has not
            // already been initialized.
            structMade[ls->getName() + callName] = true;
            // find loc of labelstatement to hash into depths.
            std::string lsloc = ls->getBeginLoc().printToString(*sm);
            lsloc = lsloc.substr(lsloc.find(':') + 1, lsloc.find(':'));
            lsloc = lsloc.substr(0, lsloc.find(':'));
            // only those call are required to have the structs initialized
            // which are at depth of there parent.
            llvm::errs() << callDepths[callName + callLoc] << " "
                         << depths[callName + lsloc] << "\n";
            // checking if the depths of the call and the label statement it
            // refers to is same.
            if (callDepths[callName + callLoc] ==
                depths[callRels[callName + callLoc]]) {
              llvm::errs() << "inside final:\n";
              // sourceLoc = ce->getBeginLoc();
              ss2 << "struct s_" << callRels[callName + callLoc] << " s"
                  << callRels[callName + callLoc] << ";\n";
              // emit all the vars in the scope of that call.
              // add check to only emit if the var is not redefined in the
              // corresponding block.
              // the above comment is old and i have added the check to this
              // in the block when the variables are being rewritten in the
              // corresponding block.
              // the parent structure is also to be passed it is not in the
              // scopes struct it needs to be added manually.
              ss2 << "s" << callRels[callName + callLoc] << ".s = s;\n";

              for (auto var : scopes[callRels[callName + callLoc]].vars) {
                // llvm::errs() << var.first << " " << var.second << " \n";
                ss2 << "s" << callRels[callName + callLoc] << "." << var.first
                    << " = &" << var.first << ";\n";
              }
              // llvm::errs() << ss2.str() << "\n";
              ss2 << callRels[callName + callLoc] << "(&s"
                  << callRels[callName + callLoc] << ")";
              Rewrite.ReplaceText(ce->getSourceRange(), ss2.str());
              // Rewrite.InsertText(sourceLoc, ss2.str(), true, true);
              // Rewrite.InsertTextBefore(ce->getEndLoc(), "&s" + callName);
              ss2.str("");
            }
            // case when the depths are not same. only the cases which are valid
            // are the ones in which the calls are at depth greater than the
            // label they are referring to.
            else {
              // find the depth difference between the call and the label it
              // refers to
              ss2 << callRels[callName + callLoc] << "(";
              int diff = callDepths[callName + callLoc] -
                         depths[callRels[callName + callLoc]];
              if (diff == 1) {
                // if difference is equal to one then just pass 's'.
                ss2 << "s";
              } else { // else when difference is not equal to one the pass a
                       // string.
                for (int i = 0; i < diff; i++) {
                  if (diff - i == 1) {
                    ss2 << "s";
                  } else {
                    ss2 << "s->";
                  }
                }
              }
              ss2 << ")";
              Rewrite.ReplaceText(ce->getSourceRange(), ss2.str());
              // Rewrite.InsertTextBefore(ce->getEndLoc(), "&s" + callName);
              ss2.str("");
            }
          }
        }
      }
    }

    if (const CallExpr *ce = Result.Nodes.getNodeAs<clang::CallExpr>("call")) {
      if (const FunctionDecl *fd =
              Result.Nodes.getNodeAs<clang::FunctionDecl>("parent")) {
        std::string callName =
            ce->getDirectCallee()->getNameInfo().getName().getAsString();
        std::string callLoc = ce->getBeginLoc().printToString(*sm);
        callLoc = callLoc.substr(callLoc.find(':') + 1, callLoc.find(':'));
        callLoc = callLoc.substr(0, callLoc.find(':'));
        // rewrite only those calls which are to label stmt.
        // callrels can be used here.
        if (callRels.find(callName + callLoc) != callRels.end()) {
          // if multiple call in a label stmt then only one call is to be
          // preceded by a structure definition.
          if (structMade[fd->getNameAsString() + callName] == false) {
            llvm::errs() << "entered init;\n";
            // if the call is of a label stmt and a struct for it has not
            // already been initialized.
            structMade[fd->getNameAsString() + callName] = true;
            // find loc of labelstatement to hash into depths.
            std::string fdloc = fd->getBeginLoc().printToString(*sm);
            fdloc = fdloc.substr(fdloc.find(':') + 1, fdloc.find(':'));
            fdloc = fdloc.substr(0, fdloc.find(':'));
            // only those call are required to have the structs initialized
            // which are at depth of there parent.i
            // only those call are required to have the structs initialized
            // which are at depth of there parent.
            llvm::errs() << callDepths[callName + callLoc] << " "
                         << depths[callName + fdloc] << "\n";
            // checking if the depths of the call and the label statement it
            // refers to is same.
            if (callDepths[callName + callLoc] ==
                depths[callRels[callName + callLoc]]) {
              llvm::errs() << "inside final:\n";
              // sourceLoc = ce->getBeginLoc();
              ss2 << "struct s_" << callRels[callName + callLoc] << " s"
                  << callRels[callName + callLoc] << ";\n";
              // emit all the vars in the scope of that call.
              // add check to only emit if the var is not redefined in the
              // corresponding block.
              // the above comment is old and i have added the check to this
              // in the block when the variables are being rewritten in the
              // corresponding block.
              // the parent structure is also to be passed it is not in the
              // scopes struct it needs to be added manually.
              ss2 << "s" << callRels[callName + callLoc] << ".s = s;\n";

              for (auto var : scopes[callRels[callName + callLoc]].vars) {
                // llvm::errs() << var.first << " " << var.second << " \n";
                ss2 << "s" << callRels[callName + callLoc] << "." << var.first
                    << " = &" << var.first << ";\n";
              }
              // llvm::errs() << ss2.str() << "\n";
              ss2 << callRels[callName + callLoc] << "(&s"
                  << callRels[callName + callLoc] << ")";
              Rewrite.ReplaceText(ce->getSourceRange(), ss2.str());
              // Rewrite.InsertText(sourceLoc, ss2.str(), true, true);
              // Rewrite.InsertTextBefore(ce->getEndLoc(), "&s" + callName);
              ss2.str("");
            }
            // case when the depths are not same. only the cases which are valid
            // are the ones in which the calls are at depth greater than the
            // label they are referring to.
            else {
              // find the depth difference between the call and the label it
              // refers to
              ss2 << callRels[callName + callLoc] << "(";
              int diff = callDepths[callName + callLoc] -
                         depths[callRels[callName + callLoc]];
              if (diff == 1) {
                // if difference is equal to one then just pass 's'.
                ss2 << "s";
              } else { // else when difference is not equal to one the pass a
                       // string.
                for (int i = 0; i < diff; i++) {
                  if (diff - i == 1) {
                    ss2 << "s";
                  } else {
                    ss2 << "s->";
                  }
                }
              }
              ss2 << ")";
              Rewrite.ReplaceText(ce->getSourceRange(), ss2.str());
              // Rewrite.InsertTextBefore(ce->getEndLoc(), "&s" + callName);
              ss2.str("");
            }
          }
        }
      }
    }
  }

private:
  Rewriter &Rewrite;
  SourceLocation sourceLoc;
};

//--------------------------------------------------------------------------------------------------------------------------//

class LabelRewriter : public MatchFinder::MatchCallback {
public:
  LabelRewriter(Rewriter &Rewrite, PrintingPolicy &pp)
      : Rewrite(Rewrite), pp(pp) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
    if (const DeclRefExpr *dr =
            Result.Nodes.getNodeAs<clang::DeclRefExpr>("child")) {
      if (const LabelStmt *ls =
              Result.Nodes.getNodeAs<clang::LabelStmt>("parent")) {
        std::string lsname = ls->getName();
        std::string locls = ls->getBeginLoc().printToString(*sm);
        locls = locls.substr(locls.find(':') + 1, locls.find(':'));
        locls = locls.substr(0, locls.find(':'));
        // check in the decls structure of the label statement if a decl is
        // present in a line number less than or equal to the given declrefexpr.
        // if yes skip this declrexpr. if not recursively go on checking the
        // struct scopes of the parent and so on. if found in depth less than
        // zero then the number of drenferences is equal to the number of depth
        // of the label stmt in which it was found minus the depth of the parent
        // label stmt. first don't consider the declrefexpr which are funciton
        // calls.
        if (dr->getValueKind() != 0) {
          // drloc is declref location in code. drname is the decl
          // refname.
          std::string drloc = dr->getBeginLoc().printToString(*sm);
          drloc = drloc.substr(drloc.find(':') + 1, drloc.find(':'));
          drloc = drloc.substr(0, drloc.find(':'));
          std::string drname = dr->getNameInfo().getAsString();
          std::string drtype = dr->getType().getAsString();
          llvm::errs() << drname << " " << drloc << " " << drtype << " ";

          // decloc is the location of the declaration correspondign to the use.
          // decname is the name of the declaratrion it is referring to,
          // although it would be the same.
          std::string decname = dr->getFoundDecl()->getNameAsString();
          std::string decloc =
              dr->getFoundDecl()->getBeginLoc().printToString(*sm);
          decloc = decloc.substr(decloc.find(':') + 1, decloc.find(':'));
          decloc = decloc.substr(0, decloc.find(':'));
          llvm::errs() << decname << " " << decloc << "\n";
          // now if the depth of the decalration is zero then nothing is to be
          // done.
          if (vardecldepths[decname + decloc] == 0) {
            // do nothing. global var used.
          }
          // if depth of the vardecl is same as the depth of use(use has depth
          // of labelstmt +1) and the declaration is before use then no need to
          // rewrite again.
          else if (vardecldepths[decname + decloc] ==
                       depths[lsname + locls] + 1 &&
                   stoi(decloc) <= stoi(drloc)) {
            // do nothing definition of declref is present in the block itself.
          }
          // if depth is less than the depth of the use then it is possibly from
          // some other struct. rewrite to add depthuse - depthdecl dereferences
          // on the struct.
          else if (vardecldepths[decname + decloc] <
                   depths[lsname + locls] + 1) {
            // first find the difference in depths;
            int diff =
                depths[lsname + locls] + 1 - vardecldepths[decname + decloc];
            // now indirections are to be handeled according to the dtype of the
            // of the variable.
            llvm::errs() << drname << " " << drname.length() << "\n";
            stringstream ss;
            // add appropriate dereferences in the string.
            // handeling first for integers and floats.
            if (drtype.compare("int") == 0 || drtype.compare("float") == 0) {
              ss << "(*(";
              for (int i = 0; i < diff; i++) {
                ss << "s->";
              }
              Rewrite.InsertTextBefore(dr->getBeginLoc(), ss.str());
              Rewrite.InsertTextAfterToken(dr->getBeginLoc(), "))");
              ss.str("");
            }
            // if it is a array.
            else {
              // check the dimensionality of the array.
              int dims = std::count(drtype.begin(), drtype.end(), '[');
              if (dims == 1) {
                // find the index of the access
                // drloc =
                //    drloc.substr(drloc.find(':') + 1, drloc.find(':'));
                // drloc =
                drloc.substr(0, drloc.find(':'));
                std::string i =
                    drtype.substr(drtype.find('[') + 1, drtype.find(']'));
                ss << "(";
                for (int i = 0; i < diff; i++) {
                  ss << "s->";
                }
                // Rewrite.ReplaceText(dr->getBeginLoc(), ss.str());
                Rewrite.InsertTextAfterToken(dr->getEndLoc(), ss.str());
                ss.str("");
              }
            } /* else if (drtype.find("float [") != std::string::npos) {
               // check the dims of array.
               int dims = std::count(drtype.begin(), drtype.end(), '[');
             }*/
          }
        }
      }
    }
  }

private:
  Rewriter &Rewrite;
  PrintingPolicy &pp;
};
//------------------------------------------------------------------------------------------------------------//
class LabelRenamer : public MatchFinder::MatchCallback {
public:
  LabelRenamer(Rewriter &Rewrite)
      : Rewrite(Rewrite) {}
  virtual void run(const MatchFinder::MatchResult &Result) {
    SourceManager *const sm = Result.SourceManager;
}
}
//-------------------------------------------------------------------------------------------------------------------------//
class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R, PrintingPolicy &pp)
      : globalBuilder(R), structDumper(R), labelRelBuilder(R), labelBuilder(R),
        structBuilder(R), callDepth(), structInit(R), labelRewriter(R, pp) {
    // all code from main goes here.
    // Find all the globals and labelStmt first.
    // Find all the globals and store them in struct with type and identfier.
    Finder.addMatcher(globalMatcher, &globalBuilder);
    // find all the labelStmt and store there name in a vector of strings.
    Finder.addMatcher(labelMatcher, &labelBuilder);
    // below matcher returns all node at depth level one.
    // Finder.addMatcher(labelStmt(hasParent(compoundStmt(
    //                                hasParent(functionDecl().bind("parent")))))
    //                      .bind("child"),
    //                  &labelRelBuilder);
    Finder.addMatcher(
        labelStmt(hasAncestor(functionDecl().bind("parent"))).bind("child"),
        &labelRelBuilder);
    // find the parent child relationship of label statements by matching all
    // nodes having a compound statement as parent;
    Finder.addMatcher(
        labelStmt(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &labelRelBuilder);
    // for all nodes find the variables that need to be passed on into its
    // scope.
    DelayedFinder.addMatcher(varDecl(hasAncestor(functionDecl())).bind("child"),
                             &structBuilder);

    // Next thing would be to find the depths of the call expressions, so
    // appropriate redirections for variables may be provided. first
    // finding all calls at depth one.
    DelayedFinder.addMatcher(
        callExpr(hasAncestor(functionDecl()), argumentCountIs(0))
            .bind("depth1"),
        &callDepth);
    // finding the call expressions at more depths greater than .
    DelayedFinder.addMatcher(
        callExpr(hasAncestor(labelStmt().bind("parent")), argumentCountIs(0))
            .bind("depth"),
        &callDepth);
    // now the depths are in hand the logic to initialize scope srtuctures
    // before function calls must start. The below matcher inserts structs
    // intializations for function calls before the functions at a depth level
    // of one in label statements.
    //-------------------------------------------------------------------//
    // going to find global decls needed for call resolution
    DelayedFinder.addMatcher(
        functionDecl(hasParent(translationUnitDecl())).bind("decl"),
        &globalFuncDeclFinder);
    // first going to resolve calls at depth greatewr than 1 before the
    // strutcs are emitted.
    MatchCallResolver.addMatcher(
        callExpr(hasAncestor(labelStmt().bind("parent")), argumentCountIs(0))
            .bind("call"),
        &callResolver);
    // resolve calls at depths 1
    MatchCallResolver2.addMatcher(
        callExpr(hasAncestor(functionDecl().bind("parent")), argumentCountIs(0))
            .bind("call"),
        &callResolver);
    // now finding the vars in the last level label.
    // first finding out the last label stmts. all other label stmts
    // have been marked in some previous matcher.
    // below matcher just places finds the startloc and endloc of structs.
    // LastLabelFinder.addMatcher(labelStmt().bind("label"), &labelLast);
    // need to build decls for the label stmt at innermost depth.
    LastLabelFinder.addMatcher(
        varDecl(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &labelLast);
    // finding depths for vardecls to prune from structures.
    VarDepthFinder.addMatcher(varDecl().bind("one"), &varDepthFinder);
    // for decls within labels
    VarDepthFinder.addMatcher(
        varDecl(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &varDepthFinder);
    // for decls at global level
    VarDepthFinder.addMatcher(
        varDecl(hasDeclContext(translationUnitDecl().bind("parent")))
            .bind("child"),
        &varDepthFinder);
    // rewitrefinder will try to find all the vardecl and try to get  replace
    // text at appropriate places.
    RewriteFinder.addMatcher(
        declRefExpr(hasAncestor(labelStmt().bind("parent"))).bind("child"),
        &labelRewriter);
    // Use delayedfinder2 from this point and beyond
    // after the call to structDumper the depths will be sorted. structDumper
    // has a logic to sort the depths. adding code to find the main function
    // and rewrite something there.
    // first the calls at depths greater than one have there structs intitalized
    // then the ones at depth one.
    DelayedFinder2.addMatcher(
        callExpr(hasAncestor(labelStmt().bind("parent"))).bind("call"),
        &structInit);
    // now dump the structures they will be right.
    MainDumpFinder.addMatcher(functionDecl().bind("main"), &structDumper);
    // have to add a new matcher to add structures and call before functions
    // call from any function decl. to do this in the ast matcher bind the
    // nodes parent function decl and if it is the actual parent of the label
    // corresponding to the call.
    DelayedFinder2.addMatcher(
        callExpr(hasAncestor(functionDecl().bind("parent"))).bind("call"),
        &structInit);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    // Run the matchers when we have the whole TU parsed.
    Finder.matchAST(Context);
    /*
llvm::errs() << "soucrcelocs\n";

for (auto sl : sourceLocs) {
llvm::errs() << sl.first << " " << sl.second << " ";
}
    */
    /*
    llvm::errs()<<"labels: \n";
    for(auto label : labels){
            llvm::errs()<<label<<" ";
    }
*/
    /*
         llvm::errs() << "parenchil:\n";
         for (auto chil : parenChilMap) {
           llvm::errs() << chil.first << " " << chil.second << "\n";
         }
    */

    /*
         for (auto loc : sourceLocs) {
           llvm::errs() << loc.first << " " << loc.second << "\n";
         }
     */
    // llvm::errs() << "globals\n";
    DelayedFinder.matchAST(Context);
    MatchCallResolver.matchAST(Context);
    MatchCallResolver2.matchAST(Context);
    llvm::errs() << "depths:\n";
    for (auto depth : depths) {
      llvm::errs() << depth.first << " " << depth.second << "\n";
    }

    /*
          llvm::errs() << "visitedLables\n";
          for (auto elem : visitedLabels) {
            llvm::errs() << elem.first << " " << elem.second << "\n";
          }

              llvm::errs() << "depths:\n";
              for (auto depth : depths) {
                llvm::errs() << depth.first << " " << depth.second << "\n";
              }
      */

    LastLabelFinder.matchAST(Context);
    VarDepthFinder.matchAST(Context);
    //--------------------------------------------------------------------------------------------------//
    // prune the structures to remove invalid variables being passed.
    vector<std::string> toRemove;
    for (auto &label : labels) {
      for (auto &var : scopes[label].vars) {
        if (vardecldepths[var.first +
                          to_string(scopes[label].locs[var.first])] >
            depths[label]) {
          toRemove.push_back(var.first);
        }
      }
      for (auto key : toRemove) {
        scopes[label].vars.erase(key);
      }
      toRemove.clear();
    }
    //---------------------------------------------------------------------------------------------------------------//
    RewriteFinder.matchAST(Context);
    /*
        llvm::errs() << "vardepths\n";
        or (auto depth : vardecldepths) {
          llvm::errs() << depth.first << " " << depth.second << "\n";
        }
    */
    /*
for (auto x : globalFuncDecls) {
llvm::errs() << x << " ";
}*/
    llvm::errs() << "\n";
    llvm::errs() << "callrels:\n";
    for (auto rels : callRels) {
      llvm::errs() << rels.first << " " << rels.second << "\n";
    }
    /*
                llvm::errs() << "decls:\n";
                for (auto label : labels) {
                  llvm::errs() << label << "\n";
                  for (auto var : decls[label].vars) {
                    llvm::errs() << var.first << " " << var.second << " "
                                 << decls[label].locs[var.first];
                  }
                  llvm::errs() << "\n";
                }

            */

    for (auto label : labels) {
      llvm::errs() << label << "\n";
      for (auto var : scopes[label].vars) {
        llvm::errs() << var.first << " " << var.second;
      }
      llvm::errs() << "\n";
    }

    DelayedFinder2.matchAST(Context);
    // dump the structtures.
    // MainDumpFinder.matchAST(Context);
    llvm::errs() << "calldepths:\n";
    for (auto depths : callDepths) {
      llvm::errs() << depths.first << " " << depths.second << "\n";
    }
  }

private:
  GlobalBuilder globalBuilder;
  LabelFinder labelBuilder;
  LabelRelBuilder labelRelBuilder;
  StructBuilder structBuilder;
  StructDumper structDumper;
  CallDepth callDepth;
  StructInit structInit;
  CallResolver callResolver;
  GlobalFuncDeclFinder globalFuncDeclFinder;
  LabelLast labelLast;
  VarDepthFinder varDepthFinder;
  LabelRewriter labelRewriter;
  MatchFinder Finder;
  MatchFinder MainDumpFinder;
  MatchFinder DelayedFinder;
  MatchFinder DelayedFinder2;
  MatchFinder MatchCallResolver;
  MatchFinder MatchCallResolver2;
  MatchFinder LastLabelFinder;
  MatchFinder VarDepthFinder;
  MatchFinder RewriteFinder;
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
  CreateASTConsumer(clang::CompilerInstance &Compiler,
                    llvm::StringRef InFile) override {
    this->TheRewriter.setSourceMgr(Compiler.getSourceManager(),
                                   Compiler.getLangOpts());
    PrintingPolicy printingPolicy(Compiler.getLangOpts());
    return std::unique_ptr<clang::ASTConsumer>(
        new MyASTConsumer(this->TheRewriter, printingPolicy));
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
