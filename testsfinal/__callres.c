struct s_foe96 {
int * z;
int * a;
};

struct s_foo85 {
int * a;
};

struct s_foebar31 {
int * a;
};

struct s_foe37 {
int * a;
};

struct s_foo49 {
struct s_foe37 *__s;
int * x;
int * y;
};

struct s_print43 {
struct s_foe37 *__s;
int * x;
int * y;
};

struct s_foobar53 {
struct s_foo49 *__s;
};

void foebar31( struct s_foebar31*);
void foe37( struct s_foe37*);
void print43( struct s_print43*);
void foo49( struct s_foo49*);
void foobar53( struct s_foobar53*);
void foo85( struct s_foo85*);
void foe96( struct s_foe96*);


//------------------------------------------//
// This test case demonstrates the call res // 
// olution capibility of the tool. It has m //
// ultiple labels with the same name in dif //
// ferent scopes, namely the label foo. the //
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
	
struct s_foebar31 sfoebar31;
sfoebar31.a = &a;


	
struct s_foe37 sfoe37;
sfoe37.a = &a;

// this is a call to the label itself.
foe37(&sfoe37);
}


int main(){
	// since no lable named foo is declared till now,
	// this call resolves to global function foo.
	foo();
	int a = 0;
	
struct s_foo85 sfoo85;
sfoo85.a = &a;

	// this call should resolve to the label foo,
	// since it is the closest definition to it.
	foo85(&sfoo85);
	int z = 3;
	//t
	
struct s_foe96 sfoe96;
sfoe96.z = &z;
sfoe96.a = &a;
			
	foe96(&sfoe96);
	// As no definition of bar is present this call
	// should resolve to global function bar.
	bar();
	return 0;
}


void foebar31( struct s_foebar31* __s ){

		printf("In foebar!!!\n");
	}

void foe37( struct s_foe37* __s ){

	int y, x;
	//the name is same as foo in main. but due to renmaing 
	// this case is easily handeled.
	
struct s_print43 sprint43;
sprint43.__s = __s;
sprint43.x = &x;
sprint43.y = &y;

	
struct s_foo49 sfoo49;
sfoo49.__s = __s;
sfoo49.x = &x;
sfoo49.y = &y;

		// since a labeled named foo is present in the scope
		// this call must resolve to it. Note that a label 
		// named foo is also present in main(), this call 
		// should not resolve to it.
		foo49(&sfoo49);
	}

void print43( struct s_print43* __s ){

		printf("'x' in foe inside bar is: %d\n", (*(__s->x)));					//should print 1.	
		printf("'y' in foe inside bar is: %d\n", (*(__s->y)));					//should print 0.
	}

void foo49( struct s_foo49* __s ){

		printf("in foo inside foe!!!\n");
		
struct s_foobar53 sfoobar53;
sfoobar53.__s = __s;

			//this is a call to the label foobar just defined.
			foobar53(&sfoobar53);
		}

void foobar53( struct s_foobar53* __s ){

			(*(__s->__s->x)) = 0;
			(*(__s->__s->x)) = (*(__s->__s->x)) + 1;
			(*(__s->__s->y)) = 0;
			// the closest valid label to this call is the 
			// label foebar it should resolve to it.
			struct s_foebar31 sfoebar3160;
sfoebar3160.a = __s->__s->__s->a;
foebar31(&sfoebar3160);	
			// this call resolves to the print label inside foe.
			// and prints out the values of x and y.	
			struct s_print43 sprint4363;
sprint4363.__s = __s->__s->__s;
sprint4363.x = __s->__s->x;
sprint4363.y = __s->__s->y;
print43(&sprint4363);	
			}

void foo85( struct s_foo85* __s ){

		printf("in foo inside main!!!\n");
		printf("'a' in foo inside main is: %d\n", (*(__s->a)));													//should print 0.
	}

void foe96( struct s_foe96* __s ){

		printf("'a' in foo inside main is: %d\n", (*(__s->a)));													//should print 0.
		printf("'z' in foo inside main is: %d\n", (*(__s->z)));													//should print 3.
	}

