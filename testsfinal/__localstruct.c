struct s_foo54 {
};

struct s_label35 {
};

struct s_foe70 {
struct s_foo54 *__s;
};

struct s_bar62 {
struct s_foo54 *__s;
};

struct point{

		int e, f;
	};

struct point49{

			int x, y;
			struct point49 * p;
		};

struct point58{

			int a, b;
		};

struct point74{

				int c, d;
			};

void label35( struct s_label35*);
void foo54( struct s_foo54*);
void bar62( struct s_bar62*);
void foe70( struct s_foe70*);


//------------------------------------------//
// This exapmle demostrates structures struc//
// ture renaming. labels foo, bar and foe		//
// all declare a strucutre named point in   //
// themselves. now all of them have to be   //
// hoisted to a global level just so that th//
// remain in the scope of the label of which//
// they are defined. Also their varibles and//
// they themselves are to be renamed appropr//
// iately.                                  //
// compiler error will be generated in the  //
// for the rewritten code if resolution happ//
// ens incorrectly just because the variable//
// s inside the structs are of different nam//
// es and if name resolution is incorrect   //
// then the varible being used will not be  //
// found.																		//
// EXPECTED OUTPUT													// 
// 1 1              												//
// 2 2              												//
// 2 2              												//
// 3 3              												//
//------------------------------------------//

#include<stdio.h>




void hey(){
	
struct s_label35 slabel35;

label35(&slabel35);
}


int main(){
	

	
struct s_foo54 sfoo54;

	foo54(&sfoo54);
			struct point49 p2;													//this should resolve to point defined in main, and should be renamed.
			p2.x = 2;																	//this line will give compiler error if resolved incorrectly.
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	hey();
	return 0;
}



void label35( struct s_label35* __s ){

	struct point p;														//this should resolve to point defined globally as no definitions is presetn in scope.
		p.e = 3;                                //this line will give compiler error if resolved incorrectly.
		p.f = 3;
		printf("%d %d\n", p.e, p.f);	
}

void foo54( struct s_foo54* __s ){
		
	

		
struct s_bar62 sbar62;
sbar62.__s = __s;

		
struct s_foe70 sfoe70;
sfoe70.__s = __s;

	bar62(&sbar62);
	foe70(&sfoe70);
}

void bar62( struct s_bar62* __s ){

			struct point58 p1;													//this should resolve to point defined in foo, and should be renamed.
			p1.a = 1;																	//this line will give compiler error if resolved incorrectly.
			p1.b = 1;
			printf("%d %d\n", p1.a, p1.b);
		}

void foe70( struct s_foe70* __s ){

			

			struct point74 p2;													//this should resolve to point defined locally, and should be renmaed.
			p2.c = 2;																	//this line will give compiler error if resolved incorrectly. 		
			p2.d = 2;																	
			printf("%d %d\n", p2.c, p2.d);
		}

