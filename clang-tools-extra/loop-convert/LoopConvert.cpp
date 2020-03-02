// Declares clang::SyntaxOnlyAction.
#include "/home/navdeep/work/projects/llvm-install/include/clang/Frontend/FrontendActions.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Tooling/CommonOptionsParser.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Tooling/Tooling.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/ASTMatchers/ASTMatchers.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/ASTMatchers/ASTMatchFinder.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/AST/ASTContext.h"
#include "/home/navdeep/work/projects/llvm-install/include/clang/Basic/SourceManager.h"
#include <vector>
#include <string>
#include <unordered_map>
// Declares llvm::cl::extrahelp.
#include "/home/navdeep/work/projects/llvm-install/include/llvm/Support/CommandLine.h"

struct GlobalVars{
	std::string name;
	std::string type;
};

struct scope{
    std::string name;
    std::unordered_map<std::string, std::string> vars;
};

std::vector<GlobalVars> globalVars;
std::vector<std::string > labels;
std::unordered_map< std::string, std::string> parenChilMap;
std::unordered_map<std::string, scope> scopes;

using namespace clang::SrcMgr; 
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;
using namespace clang;
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------//
static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp("\nMore help text...\n");
//----------------------------------------------------------------------------------------------------------------------------------------------//
//logic to convert the depth into a sorted list depthsorted.

typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
std::unordered_map<std::string, int> depths;

Comparator compFunctor = [](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
			{
				return elem1.second < elem2.second;
			};

std::set<std::pair<std::string, int>, Comparator> depthSorted;
//----------------------------------------------------------------------------------------------------------------------------------------------//
/*
StatementMatcher LoopMatcher =
  forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
    hasInitializer(integerLiteral(equals(0)))))))).bind("forLoop");
*/

DeclarationMatcher globalMatcher = varDecl(hasDeclContext(translationUnitDecl())).bind("global");
StatementMatcher labelMatcher = labelStmt().bind("label");

class GlobalBuilder : public MatchFinder::MatchCallback {
public :

    GlobalVars temp;

    virtual void run(const MatchFinder::MatchResult &Result) {
      ASTContext *Context = Result.Context;     
      if (const VarDecl *vd = Result.Nodes.getNodeAs<clang::VarDecl>("global")){
		temp.type = vd->getType().getAsString();
		//llvm::errs()<<vd->getType().getAsString()<<"\n";
	        temp.name = vd->getQualifiedNameAsString();
		globalVars.push_back(temp);
      }
    }
};


class LabelFinder : public MatchFinder::MatchCallback {
public :
    virtual void run(const MatchFinder::MatchResult &Result) {    
      if (const LabelStmt *ls = Result.Nodes.getNodeAs<clang::LabelStmt>("label")){
		labels.push_back(ls->getName());
      }
    }
};

/*
class LabelRelBuilder : public MatchFinder::MatchCallback {
public :
    virtual void run(const MatchFinder::MatchResult &Result) {
      SourceManager *sm = Result.SourceManager;
      if (const LabelStmt *ls = Result.Nodes.getNodeAs<clang::LabelStmt>("child")){
	      if (const LabelStmt *lp = Result.Nodes.getNodeAs<clang::LabelStmt>("parent")){
	       llvm::errs()<<"Hello"<< lp->getName();
	       parenChilMap[ls->getName()] = lp->getName();
	       //llvm::errs()<<parenChilMap[ls->getName()];
	      }
      }
    }
};
*/

class LabelRelBuilder : public MatchFinder::MatchCallback{
    public:
    virtual void run(const MatchFinder::MatchResult &Result){
        SourceManager *sm = Result.SourceManager;
        if (const LabelStmt *ls = Result.Nodes.getNodeAs<clang::LabelStmt>("child")){
            if (const LabelStmt *lp = Result.Nodes.getNodeAs<clang::LabelStmt>("parent")){
		    llvm::errs()<<"case1: \n";
		parenChilMap[ls->getName()] = lp->getName();
                depths[ls->getName()] = depths[lp->getName()] + 1; 
            }
            else if (const FunctionDecl *fd = Result.Nodes.getNodeAs<clang::FunctionDecl>("parent")){
		    llvm::errs()<<"case2: \n";
		    parenChilMap[ls->getName()] = fd->getNameAsString();
                //assuming that the nodes are visited in order of depth
                depths[ls->getName()] = 1; 
            }
        }
    }
};


class StructBuilder : public MatchFinder::MatchCallback {
public :
    virtual void run(const MatchFinder::MatchResult &Result) {
      SourceManager* const sm = Result.SourceManager;
      if (const LabelStmt *ls = Result.Nodes.getNodeAs<clang::LabelStmt>("child")){
              if (const CompoundStmt *cs = Result.Nodes.getNodeAs<clang::CompoundStmt>("parent")){
		      std::string loc =  ls->getBeginLoc().printToString(*sm);
		      loc = loc.substr(loc.find(':') + 1, loc.find(':'));
	      	      loc = loc.substr(0,loc.find(':')); 	      
		      //llvm::errs()<<loc<<"\n";
		      //iterate through all children and visit all declstmt and then vardecl. get there type and store in scopes struct
		      //llvm::errs()<<"label\n";
		      for(auto child  = cs->child_begin(); child != cs->child_end() ;child++){
           	      if(const clang::DeclStmt *ds = dyn_cast<clang::DeclStmt>(*child)){ 
			    for(auto child2 = ds->decl_begin(); child2 != ds->decl_end(); child2++){
                            if(const clang::VarDecl *vd = dyn_cast<clang::VarDecl>(*child2)){
                                    std::string varloc =  vd->getBeginLoc().printToString(*sm);
                                    varloc = varloc.substr(varloc.find(':') + 1, varloc.find(':'));
                                    varloc = varloc.substr(0,varloc.find(':'));
                                    //llvm::errs()<<varloc<<"\n";
                                    //if line number of varibale is less than line number of compound stmt add it to its scope.
                                    if(std::stoi(varloc) <= std::stoi(loc)){
					    //llvm::errs()<<ls->getName()<<"\n";
					    //llvm::errs()<<vd->getQualifiedNameAsString()<<"\n";
					    //llvm::errs()<<vd->getType().getAsString()<<"\n";
					    scopes[ls->getName()].name = ls->getName();
                                            scopes[ls->getName()].vars[vd->getQualifiedNameAsString()] = vd->getType().getAsString();                        
                                    }
                            }
                        }
                }
		}//llvm::errs()<<"child\n";
	      }
      }
    }
};

//----------------------------------------------------------------------------------------main starts------------------------------------------------------------------------------------------------------------//
int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
//Find all the globals and labelStmt first.
  GlobalBuilder globalBuilder;
  LabelFinder labelBuilder;
  LabelRelBuilder labelRelBuilder;
  StructBuilder structBuilder;
  MatchFinder Finder;
//Find all the globals and store them in struct with type and identfier.
  Finder.addMatcher(globalMatcher, &globalBuilder);
//find all the labelStmt and store there name in a vector of strings.
  Finder.addMatcher(labelMatcher, &labelBuilder);
//find the parent child relationship of label statements by matching all nodes having a compound statement as parent;
  Finder.addMatcher(labelStmt(hasParent(compoundStmt(hasParent(labelStmt().bind("parent"))))).bind("child"), &labelRelBuilder);
//below matcher returns all node at depth level one.
  Finder.addMatcher(labelStmt(hasParent(compoundStmt(hasParent(functionDecl().bind("parent"))))).bind("child"), &labelRelBuilder);
  
  /*
  for(auto label : labels){  
  	llvm::errs()<<label<<"\n";
  }*/

//need to add the nodes immediately nested in main to the parenChilMap.
//Finder.addMatcher(labelStmt(hasParent(compoundStmt(hasParent(functionDecl(hasName("main")).bind("parent"))))).bind("child"), &labelRelBuilder);
//not removing above logic right now but going to find thte variable to build up scope struct.
//for all nodes find the variables that need to be passed on into its scope.
  Finder.addMatcher(labelStmt(hasParent(compoundStmt().bind("parent"))).bind("child"), &structBuilder); 
  Tool.run(newFrontendActionFactory(&Finder).get());
  for(auto label : labels){
  	llvm::errs()<<"child "<<label<<" parent"<<parenChilMap[label]<<"\n";
  } 

  for (auto label: labels){
	  llvm::errs()<<scopes[label].name<<": ";
  	  for(auto it : scopes[label].vars){
	  	llvm::errs()<<it.first<<" "<<it.second<<" ";
	  }
	  llvm::errs()<<"\n";
  }
  llvm::errs()<<"\n depths";

  depthSorted = std::set<std::pair<std::string, int>, Comparator>(depths.begin(), depths.end(), compFunctor);
  for (auto depth : depthSorted ){
  	llvm::errs() << depth.first<<" "<<depth.second<<"\n";
  }


    return 0;
}

