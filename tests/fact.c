#include <stdio.h>

int main() {
int a;
foo : {
  int b = 5;
  int res = 1;
fact : {
  if (b == 1) {
    return;
  } else {
    res *= b;
    b--;
    fact();
  }
}

  fact();
  printf("%d: \n", res);
}
	foo();
  return 0;
}
