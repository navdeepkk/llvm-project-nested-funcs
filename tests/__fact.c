struct s_foo8 {
};

struct s_fact11 {
struct s_foo8 *__s;
int * res;
int * b;
};



void foo8( struct s_foo8*);
void fact11( struct s_fact11*);
//intended output
//first change b to the number of which factorial is calculated
//output: factorial of that number

#include <stdio.h>

int main() {
struct s_foo8 sfoo8;


	foo8(&sfoo8);
  return 0;
}


void foo8( struct s_foo8* __s )  {
  int b = 5;
  int res = 1;
struct s_fact11 sfact11;
sfact11.__s = __s;
sfact11.res = &res;
sfact11.b = &b;


  fact11(&sfact11);
  printf("%d: \n", res);
}

void fact11( struct s_fact11* __s )  {
  if ((*(__s->b)) == 1) {
    return;
  } else {
    (*(__s->res)) *= (*(__s->b));
    (*(__s->b))--;
    fact11(__s);
  }
}

