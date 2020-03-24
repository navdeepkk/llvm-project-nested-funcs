struct s_label29 {
};

struct s_foo31 {
struct s_label29 *__s;
int* x;
};

void label29( struct s_label29*);
void foo31( struct s_foo31*);
#include<stdio.h>

/*
struct point{
			int x, y;
		};

int main(){
	foo:{
	struct point{
			int x, y;
		};
		bar:{
			struct point p1;
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}
	bar();
	}
	foo();
	return 0;
}


*/
int y = 5;
int main(){
	struct s_label29 slabel29;


	label29(&slabel29);
	return 0;
}



void label29( struct s_label29* __s ){
			static int x = 5;
		struct s_foo31 sfoo31;
sfoo31.__s = __s;
sfoo31.x = &x;

		foo31(&sfoo31);
	}

void foo31( struct s_foo31* __s ){
			int z = 5;
			printf("%d\n",(*(__s->x)));
			printf("%d\n",y);
			printf("%d\n",z);
		}

