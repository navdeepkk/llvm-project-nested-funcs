struct s_foo6 {
};

struct s_bar20 {
struct s_foo6 *__s;
struct point9 * p;
};

struct point9 {

    int x, y;
  };

void foo6( struct s_foo6*);
void bar20( struct s_bar20*);


#include <stdio.h>

int main() {


struct s_foo6 sfoo6;


  
  int x;

	foo6(&sfoo6);
  return 0;
}


void foo6( struct s_foo6* __s )  {

   
 

  struct point9 p;
	p.x = 1;
	p.y = 2;
	printf("x:%d y:%d\n", p.x, p.y);


struct s_bar20 sbar20;
sbar20.__s = __s;
sbar20.p = &p;

bar20(&sbar20);
}

void bar20( struct s_bar20* __s )  {

  
  int p;
}

