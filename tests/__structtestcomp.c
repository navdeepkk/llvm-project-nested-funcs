struct s_foo30 {
};

struct s_bar38 {
struct s_foo30 *__s;
};

struct s_foe46 {
struct s_foo30 *__s;
};

struct point33{

			int x, y;
		};

struct point5{

		int x, y;
	};

struct point25{

			int x, y;
		};

void foo30( struct s_foo30*);
void bar38( struct s_bar38*);
void foe46( struct s_foe46*);


#include<stdio.h>

void hey(){
	


	struct point5 p;
		p.x = 3;
		p.y = 3;
		printf("%d %d\n", p.x, p.y);
	
}


struct point{

			int x, y;
		};

int main(){
	

	
struct s_foo30 sfoo30;

	foo30(&sfoo30);
			struct point25 p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	hey();
	return 0;
}



void foo30( struct s_foo30* __s ){
		
	

		
struct s_bar38 sbar38;
sbar38.__s = __s;

		
struct s_foe46 sfoe46;
sfoe46.__s = __s;

	bar38(&sbar38);
	foe46(&sfoe46);
}

void bar38( struct s_bar38* __s ){

			struct point33 p1;
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}

void foe46( struct s_foe46* __s ){

			struct point33 p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
		}

