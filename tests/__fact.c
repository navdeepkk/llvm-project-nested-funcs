struct s_foo9 {
};

struct s_fact14 {
struct s_foo9 *__s;
int * res;
int * b;
};



void foo9( struct s_foo9*);
void fact14( struct s_fact14*);
//intended output
//first change b to the number of which factorial is calculated
//output: factorial of that number

#include <stdio.h>

int main() {

struct s_foo9 sfoo9;


	foo9(&sfoo9);
  return 0;
}


void foo9( struct s_foo9* __s )  {

  int b = 5;
  int res = 1;

struct s_fact14 sfact14;
sfact14.__s = __s;
sfact14.res = &res;
sfact14.b = &b;


  fact14(&sfact14);
  printf("factorial is: %d \n", res);
}

void fact14( struct s_fact14* __s )  {

  if ((*(__s->b)) == 1) {
    return;
  } else {
    (*(__s->res)) *= (*(__s->b));
    (*(__s->b))--;
    fact14(__s);
  }
}

