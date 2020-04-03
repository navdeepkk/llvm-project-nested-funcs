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
