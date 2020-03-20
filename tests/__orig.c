struct s_foo6 {
int* x;
};

void foo6( struct s_foo6*);
#include<stdio.h>

void main(){
	int x = 3;
	
	struct s_foo6 sfoo6;
sfoo6.x = &x;



	foo6(&sfoo6);
	
	foo6(&sfoo6);

	foo6(&sfoo6);

	printf("x is: %d\n", x);

}


void foo6( struct s_foo6* __s ){
		printf("x is: %d\n", (*(__s->x)));
		(*(__s->x))++;
	}

