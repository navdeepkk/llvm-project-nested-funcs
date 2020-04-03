//------------------------------------------//
// This test case is an extension of the    //
// fact test case and demonsrates that scop //
// are being captures correctly and also th //
// e values of variables is retained when   //
// a label is called again. fact() when call//
// the second time does nothing, as the val //
// ue of b and res is now one. the third ca //
// ll should work perfectly fine and print  //
// out 720.																	//
// EXPECTED OUTPUT													//
// x inside foo is: 1                       //
// x inside foo inside if is: 1             //
// factorial is: 120                        //
// factorial is: 120                        //
// factorial is: 720                        //
//------------------------------------------//

#include<stdio.h>

int x = 0;

int main() {
	int a;
	foo : {
		x = x + 1;								//this x should resolve to the global var x.
		printf("x inside foo if is: %d\n", x);
		int b = 5;
		int res = 1;
		if (res == 1) {
			int x;
			x = 3;									//this x should resolve to the local var x.
			printf("x inside foo inside if is: %d\n", x);
		fact : {
			if (b == 1) {
				return;
			} else {
				res *= b;
				b--;
				fact();
			}
		}
			fact();									//this call will calculate the factorial.
			printf("factorial is :%d \n", res);
			fact();									//this call should return without doing anyhting as b has already been reduced to 1 and shoul print 120.
			printf("factorial is :%d \n", res);
			b = 6;
			res = 1;  
			fact();									//this call should return the factorial 6 as b and res have been restored once again.
			printf("factorial is :%d \n", res);
		}
	}

	a = 1;											//this varible should refer to the local a defined in main.
	if(a == 1){
		foo();
	}

	return 0;
}
