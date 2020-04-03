struct s_foebar26 {
int * a;
};

struct s_foe32 {
int * a;
};

struct s_foo68 {
};

struct s_foo36 {
struct s_foe32 *__s;
int * x;
int * y;
};

struct s_foobar40 {
struct s_foo36 *__s;
};

void foebar26( struct s_foebar26*);
void foe32( struct s_foe32*);
void foo36( struct s_foo36*);
void foobar40( struct s_foobar40*);
void foo68( struct s_foo68*);


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
	
struct s_foebar26 sfoebar26;
sfoebar26.a = &a;


	
struct s_foe32 sfoe32;
sfoe32.a = &a;

// this is a call to the label itself.
foe32(&sfoe32);
}


int main(){
	// since no lable named foo is declared till now,
	// this call resolves to global function foo.
	foo();

	
struct s_foo68 sfoo68;

	// this call should resolve to the label foo,
	// since it is the closest definition to it.
	foo68(&sfoo68);

	// As no definition of bar is present this call
	// should resolve to global function bar.
	bar();
	return 0;
}


void foebar26( struct s_foebar26* __s ){

		printf("In foebar!!!\n");
	}

void foe32( struct s_foe32* __s ){

	int y, x;
	
struct s_foo36 sfoo36;
sfoo36.__s = __s;
sfoo36.x = &x;
sfoo36.y = &y;

		// since a labeled named foo is present in the scope
		// this call must resolve to it. Note that a label 
		// named foo is also present in main(), this call 
		// should not resolve to it.
		foo36(&sfoo36);
	}

void foo36( struct s_foo36* __s ){

		printf("in foo inside foe!!!\n");
		
struct s_foobar40 sfoobar40;
sfoobar40.__s = __s;

			//this is a call to the label foobar just defined.
			foobar40(&sfoobar40);
		}

void foobar40( struct s_foobar40* __s ){

			(*(__s->__s->__s->a));								
			(*(__s->__s->x)) = (*(__s->__s->x)) + 1;
			// the closest valid label to this call is the 
			// label foebar it should resolve to it.
			struct s_foebar26 sfoebar2646;
sfoebar2646.a = __s->__s->__s->a;
foebar26(&sfoebar2646);		
			}

void foo68( struct s_foo68* __s ){

		printf("in foo inside main!!!\n");
	}

