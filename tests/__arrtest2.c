struct s_foo10 {
int* b;
int* a;
};

struct s_fun18 {
struct s_foo10 *__s;
};

void foo10( struct s_foo10*);
void fun18( struct s_fun18*);
#include<stdio.h>


int main()
{

	int a[5];
	int b = 0;

	struct s_foo10 sfoo10;
sfoo10.b = &b;
sfoo10.a = &a;


	foo10(&sfoo10);
/*verification*/
	printf("a[5] = ");
	for(int i = 0;i<5;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	
	return 0;
}


// expected output : 
// a[5] = 7 0 9 0 0
// a[3] = 0 0 3
// or garbage values in place of 0


void foo10( struct s_foo10* __s ){
		(__s->a)[0] = 7;

		if((*(__s->b))==1) // i.e. if called by fun
		{
			(__s->a)[2] = 9;
		}
		
		struct s_fun18 sfun18;
sfun18.__s = __s;

		
		if((*(__s->b))==0) //i.e. if called by main
		{
			fun18(&sfun18);
		}

	     }

void fun18( struct s_fun18* __s ){
			int a[3];
			
			a[2] = 3;
			(*(__s->__s->b)) = 1;
			foo10(__s->__s);
			
  		     }

