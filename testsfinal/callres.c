//------------------------------------------//
// This test case demonstrates the call res // 
// olution capibility of the tool. It has m //
// ultiple labels with the same name in dif //
// ferent scopes, namely labels foo and foe //
// calls are resolved appropriately to the  //
// closest label in scope. if no such label //
// is present it resolves to a global funct //
// tion. the tool assumes that all calls ar //
// e valid.                                 //
// EXPECTED OUTPUT													//
// in global foo!!!				   								//
// in foo inside main!!!										//
// 'a' in foo inside main is: 0							//		
// 'a' in foo inside main is: 0							//
// 'z' in foo inside main is: 3							//
// in foo inside foe!!!											//
// In foebar!!!															//
// 'x' in foe inside bar is: 1							//
// 'y' in foe inside bar is: 0							//				
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
	//the name is same as foo in main. but due to renmaing 
	// this case is easily handeled.
	print:{
		printf("'x' in foe inside bar is: %d\n", x);					//should print 1.	
		printf("'y' in foe inside bar is: %d\n", y);					//should print 0.
	}
	foo:{
		printf("in foo inside foe!!!\n");
		foobar:{
			x = 0;
			x = x + 1;
			y = 0;
			// the closest valid label to this call is the 
			// label foebar it should resolve to it.
			foebar();	
			// this call resolves to the print label inside foe.
			// and prints out the values of x and y.	
			print();	
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
	int a = 0;
	foo:{
		printf("in foo inside main!!!\n");
		printf("'a' in foo inside main is: %d\n", a);													//should print 0.
	}
	// this call should resolve to the label foo,
	// since it is the closest definition to it.
	foo();
	int z = 3;
	//t
	foe:{
		printf("'a' in foo inside main is: %d\n", a);													//should print 0.
		printf("'z' in foo inside main is: %d\n", z);													//should print 3.
	}			
	foe();
	// As no definition of bar is present this call
	// should resolve to global function bar.
	bar();
	return 0;
}
