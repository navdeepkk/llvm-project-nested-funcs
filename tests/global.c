//intended output
//1 1

#include<stdio.h>

int  a = 0;

int main(){
	int b = 1;
	foo:{
			a = a + 1;
			b = b + 1; 
		}
	foo();
	printf("%d\n", a);
	printf("%d\n", b);
	
	return 0;
}
