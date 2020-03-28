//intended output
//first change b to the number of which factorial is calculated
//output: factorial of that number

#include <stdio.h>

int main() {
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
  printf("factorial is: %d \n", res);
}
	foo();
  return 0;
}
