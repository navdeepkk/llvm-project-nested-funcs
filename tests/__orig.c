struct s_foo9 {
int * x;
};



void foo9( struct s_foo9*);
//intended output
//3 4 5 6 

#include<stdio.h>

void main(){
	int x = 3;
	
	struct s_foo9 sfoo9;
sfoo9.x = &x;



	foo9(&sfoo9);
	
	foo9(&sfoo9);

	foo9(&sfoo9);

	printf("x is: %d\n", x);

}


void foo9( struct s_foo9* __s ){
		printf("x is: %d\n", (*(__s->x)));
		(*(__s->x))++;
	}

