struct s_foo11 {
int * b;
};

void foo11( struct s_foo11*);


//intended output
//1 1

#include<stdio.h>

int  a = 0;

int main(){
	int b = 1;
	
struct s_foo11 sfoo11;
sfoo11.b = &b;

	foo11(&sfoo11);
	printf("%d\n", a);
	printf("%d\n", b);
	
	return 0;
}


void foo11( struct s_foo11* __s ){

			a = a + 1;
			(*(__s->b)) = (*(__s->b)) + 1; 
		}

