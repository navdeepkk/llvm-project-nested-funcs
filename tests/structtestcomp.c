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
	struct point{
		int x, y;
	};

	struct point p;														//this should resolve to point defined in hey.
		p.x = 3;
		p.y = 3;
		printf("%d %d\n", p.x, p.y);
	
}

struct point{
			int x, y;
		};

int main(){
	struct point{
			int x, y;
		};
	foo:{		
	struct point{
			int x, y;
		};
		bar:{
			struct point p1;													//this should resolve to point defined in foo.
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}
		foe:{
			struct point p2;													//this should resolve to point defined in foo.
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
		}
	bar();
	foe();
}
	foo();
			struct point p2;													//this should resolve to point defined in main.
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	hey();
	return 0;
}

