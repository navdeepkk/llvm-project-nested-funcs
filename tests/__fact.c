struct s_foo17 {
};

struct s_fact22 {
struct s_foo17 *__s;
int * res;
int * b;
};

void foo17( struct s_foo17*);
void fact22( struct s_fact22*);


//------------------------------------------//
// This test case demostrates the tools cap // 
// ability to support direct recursion. the //
// code computes the factorial of a number  //
// which is to be stored in the variable b. //
// Note that b is not present in the scope  //
// of the label fact and it is captured fro //
// m the enclosing scope.                   //
// EXPECTED OUTPUT													//
// factorial is: 120                        //
//------------------------------------------//

#include <stdio.h>

int main() {

struct s_foo17 sfoo17;

	foo17(&sfoo17);
  return 0;
}


void foo17( struct s_foo17* __s )  {

  int b = 5;
  int res = 1;

struct s_fact22 sfact22;
sfact22.__s = __s;
sfact22.res = &res;
sfact22.b = &b;


  fact22(&sfact22);
  printf("factorial is: %d \n", res);
}

void fact22( struct s_fact22* __s )  {

  if ((*(__s->b)) == 1) {
    return;
  } else {
    (*(__s->res)) *= (*(__s->b));
    (*(__s->b))--;
    fact22(__s);
  }
}

