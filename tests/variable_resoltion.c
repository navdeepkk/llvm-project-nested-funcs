/*


This test case checks if variable is resolved to it's corresponding declaration as per static scoping rules
for arbitrary depth.

Current Assumption : Variable Declaration and remaining code is not mixed. i.e. all variables are declared at beginning of function/label.

More specifically it tests following cases:
Case 1: Resolution to global variable when none of the outer function contains declaration.
Case 3: At depth 1 from variable declared in function.
Case 2: Two labels at same depth, getting resolved to appropriate variable declaration.
Case 4: At depth 2 from variable declared in label at depth 2.(From any depth to any depth)
Case 5: At depth 7(randomly chosen to test if large depth is possible) from variable declared in function.
Case 6: Passing variable at depth 2 from variable declaration as call by value.
Case 7: Passing variable at depth 2 from variable declaration as call by reference.

Expected output:
Case 1 output: 
value of global after call: 0
value of global after call: 1
Case 2 output: 
a at f1 = 5
a at f2 = 7
Case 3 output: 
value of a before call to f1: 0
value of a after call to f1: 1
Case 4 output: 
value of a before call to f4: 6
value of a after call to f4: 14
Case 5 output: 
value of a before call to f1 : 5
value of a after call to f1 : 50
Case 6 output: 
value of a before call to f1: 5
value of a after call to f1: 25
Case 7 output: 
value of a before call to f1: 5
value of a after call to f1: 25

*/

#include<stdio.h>

/*commenting following define won't run that test case and also won't generate code for that test case*/
#define C1
#define C2
#define C3
#define C4
#define C5
#define C6
#define C7

int global = 0;


//Case 1: Resolution to global variable when none of the outer function contains declaration.
#ifdef C1
void case1()
{
	int a;
	printf("\nCase 1 output: ");
	f1:{
		f2:{
			   global++;
			   printf("\nvalue of global after call: %d",global);
		
		   }
		   f2();
	   }
	   printf("\nvalue of global after call: %d", global);
	   f1();
}
#endif

//Case 2: Two labels at same depth, getting resolved to appropriate variable declaration.
#ifdef C2
void case2()
{
	int a = 5;
	printf("\nCase 2 output: ");

	f1:{
		printf("\na at f1 = %d",a);
	   }

	f2:{
		   int a = 7;
		   printf("\na at f2 = %d", a);
	   }

	   f1();
	   f2();

}
#endif

//Case 3: At depth 1 from variable declared in function.
#ifdef C3
void case3()
{
	int a = 0;
	printf("\nCase 3 output: ");
	
	f1:{
		a++;
	   }

	/*Case 3*/
	printf("\nvalue of a before call to f1: %d", a);
	f1();
	printf("\nvalue of a after call to f1: %d", a);
}
#endif

//case 4 :  At depth 2 from variable declared in label at depth 2.(From any depth to any depth)
#ifdef C4
void case4()
{
	int a = 2;
	printf("\nCase 4 output: ");
	f2:{
		int a = 5;
	
		f3:{
			int a = 6;
			
			f4:{
				a++;
				f5:{
					a *= 2;
				   }
				f5();
			}
			
			printf("\nvalue of a before call to f4: %d", a);
			f4();
			printf("\nvalue of a after call to f4: %d", a);
		}
		f3();
	}
	f2();
}
#endif

//case 5: At depth 7(randomly chosen to test if any depth is possible) from variable declared in function.
#ifdef C5
void case5()
{
	int a = 5;
	printf("\nCase 5 output: ");
	
	f1:{
		f2:{
			f3:{
				f4:{
					f5:{
						f6:{
							f7:{
								a = a*10;
							}
							f7();
						   }
						   f6();
					   }
					   f5();
				   }
				   f4();
			   }
			   f3();
		   }
		   f2();
	   }

	   printf("\nvalue of a before call to f1 : %d",a);
	   f1();
	   printf("\nvalue of a after call to f1 : %d",a);
}
#endif

//Case 6: Passing variable at depth 2 from variable declaration as call by value.
#ifdef C6
int _square(int x)
{
	return (x*x);
}

void case6()
{
	int a = 5;
	printf("\nCase 6 output: ");
	f1:{
		   f2:{
			      a = _square(a);
		      }
	   	f2();
	   }

	   printf("\nvalue of a before call to f1: %d", a);
	   f1();
	   printf("\nvalue of a after call to f1: %d", a);
}
#endif

//Case 7: Passing variable at depth 2 from variable declaration as call by reference.
#ifdef C7
void square(int *x)
{
	*x = ((*x)*(*x));
}

void case7()
{
	int a = 5;
	printf("\nCase 7 output: ");
	f1:{
		   f2:{
			      square(&a);
		      }
	   	f2();
	   }

	   printf("\nvalue of a before call to f1: %d", a);
	   f1();
	   printf("\nvalue of a after call to f1: %d\n", a);
}
#endif


int main()
{
	#ifdef C1
	case1();
	#endif

	#ifdef C2
	case2();
	#endif

	#ifdef C3
	case3();
	#endif

	#ifdef C4
	case4();
	#endif

	#ifdef C5
	case5();
	#endif

	#ifdef C6
	case6();
	#endif

	#ifdef C7
	case7();
	#endif
}
