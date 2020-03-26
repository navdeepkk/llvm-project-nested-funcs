struct s_foo22 {
int * a;
};

struct s_foo13 {
int * x;
};

struct s_fact28 {
struct s_foo22 *__s;
int * y;
int * x;
int * b;
int * res;
};



void foo13( struct s_foo13*);
void foo22( struct s_foo22*);
void fact28( struct s_fact28*);
//intended output
//fact is <factorial of the number b>
//y is: 1
//x is: 1


#include<stdio.h>

int x = 0;

void bar() {
  int x;
struct s_foo13 sfoo13;
sfoo13.x = &x;


  foo13(&sfoo13);
}

int main() {
  int a;
struct s_foo22 sfoo22;
sfoo22.a = &a;


a = 1;
if(a == 1){
	foo22(&sfoo22);
}
bar();
	printf("x is: %d\n", x);
  return 0;
}


void foo13( struct s_foo13* __s )  { 
	int y = 1;
	printf("y is: %d\n", y);
}

void foo22( struct s_foo22* __s )  {
	x=x+1;						//this x should resolve to the global var x.
  int b = 5;
  int res = 1;
  if (res == 1) {
    int x, y;
  struct s_fact28 sfact28;
sfact28.__s = __s;
sfact28.y = &y;
sfact28.x = &x;
sfact28.b = &b;
sfact28.res = &res;

    fact28(&sfact28);				//this call will calculate the factorial.
    fact28(&sfact28);				//this call should return without doing anyhting as b has already been reduced to 1.
    printf("fact is %d \n", res);
  }
}

void fact28( struct s_fact28* __s )  {
    if ((*(__s->b)) == 1) {
			int x;
      return;
    } else {
      (*(__s->res)) *= (*(__s->b));
      (*(__s->b))--;
      fact28(__s);
    }
  }

