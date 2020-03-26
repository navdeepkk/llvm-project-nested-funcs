struct s_foo15 {
int * b;
int  * a;
};

struct s_fun23 {
struct s_foo15 *__s;
};



void foo15( struct s_foo15*);
void fun23( struct s_fun23*);
// expected output : 
// a[5] = 7 0 9 0 0
// a[3] = 0 0 3
// or garbage values in place of 0

#include<stdio.h>


int main()
{

	int a[5];
	int b = 0;

	struct s_foo15 sfoo15;
sfoo15.b = &b;
sfoo15.a = &a;


	foo15(&sfoo15);
/*verification*/
	printf("a[5] = ");
	for(int i = 0;i<5;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	
	return 0;
}




void foo15( struct s_foo15* __s ){
		(__s->a)[0] = 7;

		if((*(__s->b))==1) // i.e. if called by fun
		{
			(__s->a)[2] = 9;
		}
		
		struct s_fun23 sfun23;
sfun23.__s = __s;

		
		if((*(__s->b))==0) //i.e. if called by main
		{
			fun23(&sfun23);
		}

	     }

void fun23( struct s_fun23* __s ){
			int a[3];
			
			a[2] = 3;
			(*(__s->__s->b)) = 1;
			foo15(__s->__s);
			
  		     }

