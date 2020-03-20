struct s_foo5 {
int* a;
};

struct s_fact8 {
struct s_foo5 *__s;
int* res;
int* b;
};

void foo5( struct s_foo5*);
void fact8( struct s_fact8*);
#include <stdio.h>

int main() {
int a;
struct s_foo5 sfoo5;
sfoo5.a = &a;


	foo5(&sfoo5);
  return 0;
}


void foo5( struct s_foo5* __s )  {
  int b = 5;
  int res = 1;
struct s_fact8 sfact8;
sfact8.__s = __s;
sfact8.res = &res;
sfact8.b = &b;


  fact8(&sfact8);
  printf("%d: \n", res);
}

void fact8( struct s_fact8* __s )  {
  if ((*(__s->b)) == 1) {
    return;
  } else {
    (*(__s->res)) *= (*(__s->b));
    (*(__s->b))--;
    fact8(__s);
  }
}

