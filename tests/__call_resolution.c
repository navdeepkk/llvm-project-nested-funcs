struct s_foo39 {
};

struct s_f122 {
};

struct s_f143 {
struct s_foo39 *__s;
};

void f122( struct s_f122*);
void foo39( struct s_foo39*);
void f143( struct s_f143*);


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
	
struct s_f122 sf122;


	printf("Line no 26 ");
	f122(&sf122);
}


int main()
{
	printf("Line no 33 ");
	foo(); /*Gets resolved to global function.*/

	/*Label with same name as another function.*/
	
struct s_foo39 sfoo39;

	
	printf("Line 46 ");
	foo39(&sfoo39);/*Gets resolved to local function.*/
}


void f122( struct s_f122* __s ){

		   printf("called foo/f1 \n");
	   }

void foo39( struct s_foo39* __s ){

		printf("called main/foo .\n");
		
struct s_f143 sf143;
sf143.__s = __s;

		printf("Line no 42  ");
		f143(&sf143);
	    }

void f143( struct s_f143* __s ){

			printf("called main/foo/f1 \n");
		}

