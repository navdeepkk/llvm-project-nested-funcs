#include <stdio.h>

int main() {

foo : {
  typedef struct {
    int x, y;
  } point;

  point p;
	p.x = 1;
	p.y = 2;
	printf("x:%d y:%d\n", p.x, p.y);

bar : {
  typedef int point;
  point p;
}
bar();
}

  typedef int i;
  i x;

	foo();
  return 0;
}
