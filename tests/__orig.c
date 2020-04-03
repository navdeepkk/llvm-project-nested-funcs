struct s_foo21 {
int * x;
};

void foo21( struct s_foo21*);


//------------------------------------------//
// this test case is the one which was pres // 
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

void main(){
	int x = 3;
	
	
struct s_foo21 sfoo21;
sfoo21.x = &x;


	foo21(&sfoo21);
	
	foo21(&sfoo21);

	foo21(&sfoo21);

	foo21(&sfoo21);

	printf("x is: %d\n", x);

}


void foo21( struct s_foo21* __s ){

		printf("x is: %d\n", (*(__s->x)));
		(*(__s->x))++;
	}

