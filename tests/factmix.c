//intended output
//fact is <factorial of the number b>
//y is: 1
//x is: 1


#include<stdio.h>

int x = 0;

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
	x=x+1;						//this x should resolve to the global var x.
  int b = 5;
  int res = 1;
  if (res == 1) {
    int x, y;
  fact : {
    if (b == 1) {
			int x;
      return;
    } else {
      res *= b;
      b--;
      fact();
    }
  }
    fact();				//this call will calculate the factorial.
    fact();				//this call should return without doing anyhting as b has already been reduced to 1.
    printf("fact is %d \n", res);
  }
}
a = 1;
if(a == 1){
	foo();
}
bar();
	printf("x is: %d\n", x);
  return 0;
}
