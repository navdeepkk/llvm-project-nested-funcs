//------------------------------------------//
// This test case shows the case of varible //
// resolution when the variables are present//
// at diffenret levels. the use of the varib//
// le resolves to the nearest available defi//
// nition. In case no definitions is present//
// it resolves to the global defintion. In  //
// case a varible with same name is present //
// in some enclosing scoping and in global	//
// scope, the use resolves to the definition//
// in the nearest enclosing scope.					//
// EXPECTED OUTPUT													//
//  local 'a' before call to 'r' is: 0			//
// global 'x' before call to 's' is: 2			//	
// 'a' inside 'r'is: 1											//
// 'a' inside 'r' after redefinition is: 0  //	
// 'x' inside 'r' is: 2											//	
// 'x' inside 's' is: 3											//
// local 'a' after call to 'r' is: 1				//
// global 'x' after call to 's' is: 3				//
//------------------------------------------//
#include<stdio.h>

int x = 2, a;

int main(){
	int a = 0;
	printf("local 'a' before call to 'r' is: %d\n", a);	//should print 0.
	printf("global 'x' before call to 's' is: %d\n", x);	//should print 2.
	p:{
		q:{
			r:{
				a = 1;
				printf("'a' inside 'r'is: %d\n", a);					//this will resolve to 'a' defined in main.
				int a = 0;
				printf("'a' inside 'r' after redefinition is: %d\n", a);					//this will resolve to 'a' defined in 'r' as it is nearrest available def.
				printf("'x' inside 'r' is: %d\n", x);					//this will resolve to global x.
			}
			s:{
				x = 3;													//should update global 'x'.
				printf("'x' inside 's' is: %d\n", x);					//should print 3.
			}
			r();
			s();
		}
		q();
	}
	p();
	printf("local 'a' after call to 'r' is: %d\n", a);//should print 1 as it was passed to 'r'.
	printf("global 'x' after call to 's' is: %d\n", x);	//should print 3.

	
	return 0;
}
