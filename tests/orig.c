//intended output
//3 4 5 6 

#include<stdio.h>

void main(){
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

}
