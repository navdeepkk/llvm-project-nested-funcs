/* Expected output:

Line no 33 Called global foo()
Line no 26 called foo/f1 
Line 46 called main/foo .
Line no 42  called main/foo/f1

This test case checks if call gets resolved to their appropriate function depending on their scope.
Case 1: Label with same name as another function.
Case 2: Label with same name as other label. 
*/


#include<stdio.h>

void foo()
{
	printf("Called global foo()\n");

	/*Label with same name as other label.*/
	f1:{
		   printf("called foo/f1 \n");
	   }

	printf("Line no 26 ");
	f1();
}


int main()
{
	printf("Line no 33 ");
	foo(); /*Gets resolved to global function.*/

	/*Label with same name as another function.*/
	foo:{
		printf("called main/foo .\n");
		f1:{
			printf("called main/foo/f1 \n");
		}
		printf("Line no 42  ");
		f1();
	    }
	
	printf("Line 46 ");
	foo();/*Gets resolved to local function.*/
}
