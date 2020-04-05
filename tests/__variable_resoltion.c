struct s_f2133 {
int * a;
};

struct s_f164 {
int * a;
};

struct s_f1225 {
int * a;
};

struct s_f1114 {
int * a;
};

struct s_f1253 {
int * a;
};

struct s_f294 {
int * a;
};

struct s_f1172 {
int * a;
};

struct s_f188 {
int * a;
};

struct s_f2256 {
struct s_f1253 *__s;
};

struct s_f2175 {
struct s_f1172 *__s;
};

struct s_f3138 {
struct s_f2133 *__s;
int * a;
};

struct s_f267 {
struct s_f164 *__s;
};

struct s_f2228 {
struct s_f1225 *__s;
};

struct s_f4143 {
struct s_f3138 *__s;
int * a;
};

struct s_f3178 {
struct s_f2175 *__s;
};

struct s_f5147 {
struct s_f4143 *__s;
};

struct s_f4181 {
struct s_f3178 *__s;
};

struct s_f5184 {
struct s_f4181 *__s;
};

struct s_f6187 {
struct s_f5184 *__s;
};

struct s_f7190 {
struct s_f6187 *__s;
};

void f164( struct s_f164*);
void f267( struct s_f267*);
void f188( struct s_f188*);
void f294( struct s_f294*);
void f1114( struct s_f1114*);
void f2133( struct s_f2133*);
void f3138( struct s_f3138*);
void f4143( struct s_f4143*);
void f5147( struct s_f5147*);
void f1172( struct s_f1172*);
void f2175( struct s_f2175*);
void f3178( struct s_f3178*);
void f4181( struct s_f4181*);
void f5184( struct s_f5184*);
void f6187( struct s_f6187*);
void f7190( struct s_f7190*);
void f1225( struct s_f1225*);
void f2228( struct s_f2228*);
void f1253( struct s_f1253*);
void f2256( struct s_f2256*);


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
	
struct s_f164 sf164;
sf164.a = &a;

	   printf("\nvalue of global after call: %d", global);
	   f164(&sf164);
}
#endif

//Case 2: Two labels at same depth, getting resolved to appropriate variable declaration.
#ifdef C2
void case2()
{
	int a = 5;
	printf("\nCase 2 output: ");

	
struct s_f188 sf188;
sf188.a = &a;


	
struct s_f294 sf294;
sf294.a = &a;


	   f188(&sf188);
	   f294(&sf294);

}
#endif

//Case 3: At depth 1 from variable declared in function.
#ifdef C3
void case3()
{
	int a = 0;
	printf("\nCase 3 output: ");
	
	
struct s_f1114 sf1114;
sf1114.a = &a;


	/*Case 3*/
	printf("\nvalue of a before call to f1: %d", a);
	f1114(&sf1114);
	printf("\nvalue of a after call to f1: %d", a);
}
#endif

//case 4 :  At depth 2 from variable declared in label at depth 2.(From any depth to any depth)
#ifdef C4
void case4()
{
	int a = 2;
	printf("\nCase 4 output: ");
	
struct s_f2133 sf2133;
sf2133.a = &a;

	f2133(&sf2133);
}
#endif

//case 5: At depth 7(randomly chosen to test if any depth is possible) from variable declared in function.
#ifdef C5
void case5()
{
	int a = 5;
	printf("\nCase 5 output: ");
	
	
struct s_f1172 sf1172;
sf1172.a = &a;


	   printf("\nvalue of a before call to f1 : %d",a);
	   f1172(&sf1172);
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
	
struct s_f1225 sf1225;
sf1225.a = &a;


	   printf("\nvalue of a before call to f1: %d", a);
	   f1225(&sf1225);
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
	
struct s_f1253 sf1253;
sf1253.a = &a;


	   printf("\nvalue of a before call to f1: %d", a);
	   f1253(&sf1253);
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


void f164( struct s_f164* __s ){

		
struct s_f267 sf267;
sf267.__s = __s;

		   f267(&sf267);
	   }

void f267( struct s_f267* __s ){

			   global++;
			   printf("\nvalue of global after call: %d",global);
		
		   }

void f188( struct s_f188* __s ){

		printf("\na at f1 = %d",(*(__s->a)));
	   }

void f294( struct s_f294* __s ){

		   int a = 7;
		   printf("\na at f2 = %d", a);
	   }

void f1114( struct s_f1114* __s ){

		(*(__s->a))++;
	   }

void f2133( struct s_f2133* __s ){

		int a = 5;
	
		
struct s_f3138 sf3138;
sf3138.__s = __s;
sf3138.a = &a;

		f3138(&sf3138);
	}

void f3138( struct s_f3138* __s ){

			int a = 6;
			
			
struct s_f4143 sf4143;
sf4143.__s = __s;
sf4143.a = &a;

			
			printf("\nvalue of a before call to f4: %d", a);
			f4143(&sf4143);
			printf("\nvalue of a after call to f4: %d", a);
		}

void f4143( struct s_f4143* __s ){

				(*(__s->a))++;
				
struct s_f5147 sf5147;
sf5147.__s = __s;

				f5147(&sf5147);
			}

void f5147( struct s_f5147* __s ){

					(*(__s->__s->a)) *= 2;
				   }

void f1172( struct s_f1172* __s ){

		
struct s_f2175 sf2175;
sf2175.__s = __s;

		   f2175(&sf2175);
	   }

void f2175( struct s_f2175* __s ){

			
struct s_f3178 sf3178;
sf3178.__s = __s;

			   f3178(&sf3178);
		   }

void f3178( struct s_f3178* __s ){

				
struct s_f4181 sf4181;
sf4181.__s = __s;

				   f4181(&sf4181);
			   }

void f4181( struct s_f4181* __s ){

					
struct s_f5184 sf5184;
sf5184.__s = __s;

					   f5184(&sf5184);
				   }

void f5184( struct s_f5184* __s ){

						
struct s_f6187 sf6187;
sf6187.__s = __s;

						   f6187(&sf6187);
					   }

void f6187( struct s_f6187* __s ){

							
struct s_f7190 sf7190;
sf7190.__s = __s;

							f7190(&sf7190);
						   }

void f7190( struct s_f7190* __s ){

								(*(__s->__s->__s->__s->__s->__s->__s->a)) = (*(__s->__s->__s->__s->__s->__s->__s->a))*10;
							}

void f1225( struct s_f1225* __s ){

		   
struct s_f2228 sf2228;
sf2228.__s = __s;

	   	f2228(&sf2228);
	   }

void f2228( struct s_f2228* __s ){

			      (*(__s->__s->a)) = _square((*(__s->__s->a)));
		      }

void f1253( struct s_f1253* __s ){

		   
struct s_f2256 sf2256;
sf2256.__s = __s;

	   	f2256(&sf2256);
	   }

void f2256( struct s_f2256* __s ){

			      square(&(*(__s->__s->a)));
		      }

