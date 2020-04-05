struct s_p31 {
int * a;
};

struct s_q34 {
struct s_p31 *__s;
};

struct s_s46 {
struct s_q34 *__s;
};

struct s_r37 {
struct s_q34 *__s;
};

void p31( struct s_p31*);
void q34( struct s_q34*);
void r37( struct s_r37*);
void s46( struct s_s46*);


//------------------------------------------//
// This test case shows the case of varible //
// resolution when the variables are present//
// at diffenret levels. the use of the varib//
// le resolves to the nearest available defi//
// nition. In case no definitions is present//
// it resolves to the global defintion. In  //
// case a varible with same name is present //
// in some enclosing scoping and in global	//
// scope, the use resolves to the definition//
// in the nearest enclosing scope.					//
// EXPECTED OUTPUT													//
//  local 'a' before call to 'r' is: 0			//
// global 'x' before call to 's' is: 2			//	
// 'a' inside 'r'is: 1											//
// 'a' inside 'r' after redefinition is: 0  //	
// 'x' inside 'r' is: 2											//	
// 'x' inside 's' is: 3											//
// local 'a' after call to 'r' is: 1				//
// global 'x' after call to 's' is: 3				//
//------------------------------------------//
#include<stdio.h>

int x = 2, a;

int main(){
	int a = 0;
	printf("local 'a' before call to 'r' is: %d\n", a);	//should print 0.
	printf("global 'x' before call to 's' is: %d\n", x);	//should print 2.
	
struct s_p31 sp31;
sp31.a = &a;

	p31(&sp31);
	printf("local 'a' after call to 'r' is: %d\n", a);//should print 1 as it was passed to 'r'.
	printf("global 'x' after call to 's' is: %d\n", x);	//should print 3.

	
	return 0;
}


void p31( struct s_p31* __s ){

		
struct s_q34 sq34;
sq34.__s = __s;

		q34(&sq34);
	}

void q34( struct s_q34* __s ){

			
struct s_r37 sr37;
sr37.__s = __s;

			
struct s_s46 ss46;
ss46.__s = __s;

			r37(&sr37);
			s46(&ss46);
		}

void r37( struct s_r37* __s ){

				(*(__s->__s->__s->a)) = 1;
				printf("'a' inside 'r'is: %d\n", (*(__s->__s->__s->a)));					//this will resolve to 'a' defined in main.
				int a = 0;
				printf("'a' inside 'r' after redefinition is: %d\n", a);					//this will resolve to 'a' defined in 'r' as it is nearrest available def.
				printf("'x' inside 'r' is: %d\n", x);					//this will resolve to global x.
			}

void s46( struct s_s46* __s ){

				x = 3;													//should update global 'x'.
				printf("'x' inside 's' is: %d\n", x);					//should print 3.
			}

