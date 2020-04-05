struct s_foo42 {
};

struct s_bar50 {
struct s_foo42 *__s;
};

struct s_foe58 {
struct s_foo42 *__s;
};

struct point46{

			int x, y;
		};

struct point23{

		int x, y;
	};

struct point37{

			int x, y;
			struct point * p;
		};

void foo42( struct s_foo42*);
void bar50( struct s_bar50*);
void foe58( struct s_foe58*);


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
// EXPECTED OUTPUT													// 
// 1 1              												//
// 2 2              												//
// 2 2              												//
// 3 3              												//
//------------------------------------------//

#include<stdio.h>

void hey(){
	


	struct point23 p;														//this should resolve to point defined in hey.
		p.x = 3;
		p.y = 3;
		printf("%d %d\n", p.x, p.y);	
}


int main(){
	

	
struct s_foo42 sfoo42;

	foo42(&sfoo42);
			struct point37 p2;													//this should resolve to point defined in main.
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	hey();
	return 0;
}



void foo42( struct s_foo42* __s ){
		
	

		
struct s_bar50 sbar50;
sbar50.__s = __s;

		
struct s_foe58 sfoe58;
sfoe58.__s = __s;

	bar50(&sbar50);
	foe58(&sfoe58);
}

void bar50( struct s_bar50* __s ){

			struct point46 p1;													//this should resolve to point defined in foo.
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}

void foe58( struct s_foe58* __s ){

			struct point46 p2;													//this should resolve to point defined in foo.
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
		}

