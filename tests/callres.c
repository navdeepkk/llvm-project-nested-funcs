//intended output
//In foebar

#include<stdio.h>

int a;

void foo(){
	printf("in global foo!!!\n");
}


void bar(){
	int a;
	foebar:{
		printf("In foebar!!!\n");
	}

	foe:{
	int y, x;
	foo:{
		printf("in foo inside foe!!!\n");
		foobar:{
			a;								
			x = x + 1;
			foebar();		
			}
			foobar();
		}
		foo();
	}
foe();
}


int main(){

	foo();

	foo:{
		printf("in foo inside main!!!\n");
	}

	foo();

	bar();
	return 0;
}
