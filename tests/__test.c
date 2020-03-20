struct s_foo16 {
int* a;
};

struct s_foo7 {
int* x;
};

struct s_fact22 {
struct s_foo16 *__s;
int* y;
int* x;
int* b;
int* res;
};

void foo7( struct s_foo7*);
void foo16( struct s_foo16*);
void fact22( struct s_fact22*);
#include<stdio.h>

int x;

void bar() {
  int x;
struct s_foo7 sfoo7;
sfoo7.x = &x;


  foo7(&sfoo7);
}

int main() {
  int a;
struct s_foo16 sfoo16;
sfoo16.a = &a;


a = 1;
if(a == 1){
	foo16(&sfoo16);
}
bar();
  return 0;
}


void foo7( struct s_foo7* __s )  { 
	int y = 1;
	printf("y is: %d", y); 
}

void foo16( struct s_foo16* __s )  {
	x=x+1;
  int b = 5;
  int res = 1;
  if (res == 1) {
    int x, y;
  struct s_fact22 sfact22;
sfact22.__s = __s;
sfact22.y = &y;
sfact22.x = &x;
sfact22.b = &b;
sfact22.res = &res;

    fact22(&sfact22);
    fact22(&sfact22);
    printf("%d: \n", res);
  }
}

void fact22( struct s_fact22* __s )  {
    if ((*(__s->b)) == 1) {
			int x;
      return 0;
    } else {
      (*(__s->res)) *= (*(__s->b));
      (*(__s->b))--;
      fact22(__s);
    }
  }

