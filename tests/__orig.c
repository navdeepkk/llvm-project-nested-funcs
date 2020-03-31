struct s_foo10 {
int * x;
};

void foo10( struct s_foo10*);


//intended output
//3 4 5 6 

#include<stdio.h>

void main(){
	int x = 3;
	
	
struct s_foo10 sfoo10;
sfoo10.x = &x;


	foo10(&sfoo10);
	
	foo10(&sfoo10);

	foo10(&sfoo10);

	foo10(&sfoo10);

	printf("x is: %d\n", x);

}


void foo10( struct s_foo10* __s ){

		printf("x is: %d\n", (*(__s->x)));
		(*(__s->x))++;
	}

