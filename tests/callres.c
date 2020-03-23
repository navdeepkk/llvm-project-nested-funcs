//intended output
//In foebar

#include<stdio.h>

int a;

void bar(){
	int a;
	foebar:{
		printf("In foebar!!!\n");
	}

	foe:{
	int y, x;
	foo:{
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
bar();
return 0;
}
