struct s_foo11 {
};

struct s_bar15 {
struct s_foo11 *__s;
};

struct s_foe21 {
struct s_foo11 *__s;
};

struct point12{
			int x, y;
		};
struct point8{
			int x, y;
		};


void foo11( struct s_foo11*);
void bar15( struct s_bar15*);
void foe21( struct s_foe21*);
#include<stdio.h>

struct point{
			int x, y;
		};

int main(){
	

	struct s_foo11 sfoo11;


	foo11(&sfoo11);
			struct point8 p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	return 0;
}



void foo11( struct s_foo11* __s ){		
	

		struct s_bar15 sbar15;
sbar15.__s = __s;

		struct s_foe21 sfoe21;
sfoe21.__s = __s;

	bar15(&sbar15);
	foe21(&sfoe21);
}

void bar15( struct s_bar15* __s ){
			struct point12 p1;
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}

void foe21( struct s_foe21* __s ){
			struct point12 p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
		}

