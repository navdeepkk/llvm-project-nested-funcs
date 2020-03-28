struct s_foo25 {
int * a;
};

struct s_foo14 {
int * x;
};

struct s_fact35 {
struct s_foo25 *__s;
int * y;
int * x;
int * b;
int * res;
};

void foo14( struct s_foo14*);
void foo25( struct s_foo25*);
void fact35( struct s_fact35*);


//intended output
//fact is <factorial of the number b>
//y is: 1
//x is: 1


#include<stdio.h>

int x = 0;

void bar() {
  int x;

struct s_foo14 sfoo14;
sfoo14.x = &x;

  foo14(&sfoo14);
}

int main() {
  int a;

struct s_foo25 sfoo25;
sfoo25.a = &a;

a = 1;
if(a == 1){
	foo25(&sfoo25);
}
bar();
	printf("x is: %d\n", x);
  return 0;
}


void foo14( struct s_foo14* __s )  {
 
	int y = 1;
	printf("y is: %d\n", y);
}

void foo25( struct s_foo25* __s )  {

	x=x+1;						//this x should resolve to the global var x.
  int b = 5;
  int res = 1;
  if (res == 1) {
    int x, y;
		x = 2;				//this x should resolve to the local var x.
		printf("x inside foo inside if is: %d\n", x);
  
struct s_fact35 sfact35;
sfact35.__s = __s;
sfact35.y = &y;
sfact35.x = &x;
sfact35.b = &b;
sfact35.res = &res;

    fact35(&sfact35);				//this call will calculate the factorial.
    fact35(&sfact35);				//this call should return without doing anyhting as b has already been reduced to 1.
    printf("factorial is :%d \n", res);
  }
}

void fact35( struct s_fact35* __s )  {

    if ((*(__s->b)) == 1) {
			int x;
      return;
    } else {
      (*(__s->res)) *= (*(__s->b));
      (*(__s->b))--;
      fact35(__s);
    }
  }

