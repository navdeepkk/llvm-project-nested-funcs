#include<stdio.h>

int x;

void bar() {
  int x;
foo : { 
	int y = 1;
	printf("y is: %d\n", y); 
}
  foo();
}

int main() {
  int a;
foo : {
	x=x+1;
  int b = 5;
  int res = 1;
  if (res == 1) {
    int x, y;
  fact : {
    if (b == 1) {
			int x;
      return 0;
    } else {
      res *= b;
      b--;
      fact();
    }
  }
    fact();
    fact();
    printf("fcat is %d \n", res);
  }
}
a = 1;
if(a == 1){
	foo();
}
bar();
  return 0;
}
