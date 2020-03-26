struct s_foo23 {
};

struct s_foe33 {
struct s_foo23 *__s;
};

struct s_bar27 {
struct s_foo23 *__s;
};

struct point24{
			int x, y;
		};
struct point4{
		int x, y;
	};
struct point20{
			int x, y;
		};


void foo23( struct s_foo23*);
void bar27( struct s_bar27*);
void foe33( struct s_foe33*);
#include<stdio.h>

void hey(){
	


	struct point4 p;
		p.x = 3;
		p.y = 3;
		printf("%d %d\n", p.x, p.y);
	
}

struct point{
			int x, y;
		};

int main(){
	

	struct s_foo23 sfoo23;


	foo23(&sfoo23);
			struct point20 p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	hey();
	return 0;
}



void foo23( struct s_foo23* __s ){		
	

		struct s_bar27 sbar27;
sbar27.__s = __s;

		struct s_foe33 sfoe33;
sfoe33.__s = __s;

	bar27(&sbar27);
	foe33(&sfoe33);
}

void bar27( struct s_bar27* __s ){
			struct point24 p1;
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}

void foe33( struct s_foe33* __s ){
			struct point24 p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
		}

