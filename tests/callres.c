//------------------------------------------//
// This test case demonstrates the call res // 
// olution capibility of the tool. It has m //
// ultiple labels with the same name in dif //
// ferent scopes, namely th label foo. the  //
// calls are resolved appropriately to the  //
// closest label in scope. if no such label //
// is present it resolves to a global funct //
// tion. the tool assumes that all calls ar //
// e valid.                                 //
// EXPECTED OUTPUT													//
// in global foo!!!                         //
// in foo inside main!!!                    //
// in foo inside foe!!!                     //
// in foebar!!!                             //
//------------------------------------------//
#include<stdio.h>

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
			// the closest valid label to this call is the 
			// label foebar it should resolve to it.
			foebar();		
			}
			//this is a call to the label foobar just defined.
			foobar();
		}
		// since a labeled named foo is present in the scope
		// this call must resolve to it. Note that a label 
		// named foo is also present in main(), this call 
		// should not resolve to it.
		foo();
	}
// this is a call to the label itself.
foe();
}


int main(){
	// since no lable named foo is declared till now,
	// this call resolves to global function foo.
	foo();

	foo:{
		printf("in foo inside main!!!\n");
	}
	// this call should resolve to the label foo,
	// since it is the closest definition to it.
	foo();

	// As no definition of bar is present this call
	// should resolve to global function bar.
	bar();
	return 0;
}
