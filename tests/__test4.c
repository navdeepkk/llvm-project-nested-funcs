typedef 
struct {

		int x, y;
	}point;

struct s_foo16 {
point * p;
int * k;
};

void foo16( struct s_foo16*);


#include <stdio.h>


int main() {
	//typedef unsigned int ui;
	//ui i = 5, j = 8;
	int k = 9;
	
	point p;
	
struct s_foo16 sfoo16;
sfoo16.p = &p;
sfoo16.k = &k;

	foo16(&sfoo16);
	return 0;
}



void foo16( struct s_foo16* __s ){

		(*(__s->p)).x = 5;
		(*(__s->p)).y = 5;
		//printf("i = %d\n", i);
		//printf("j = %d\n", j);
		//iprintf("k = %d\n", k);
	}

