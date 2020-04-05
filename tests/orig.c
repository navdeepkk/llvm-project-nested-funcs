//------------------------------------------//
// This test case is the one which was pres // 
// ent in the the assignment writeup. It si //
// mply demostrates that the tool is able   //
// to handle labels with static scoping in  //
// play.	                                  //
// EXPECTED OUTPUT													//
// x is: 3                                  //
// x is: 4                                  //
// x is: 5                                  //
// x is: 6                                  //
// x is: 7                                  //
//------------------------------------------//

#include<stdio.h>

int main(){
	int x = 3;

	foo:{
		printf("x is: %d\n", x);								
		x++;
	}	
	
	foo();
	
	foo();

	foo();

	foo();

	printf("x is: %d\n", x);
	
	return 0;
}
