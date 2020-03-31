struct s_foe22 {
int * a;
};

struct s_foebar16 {
int * a;
};

struct s_foo49 {
};

struct s_foo26 {
struct s_foe22 *__s;
int * x;
int * y;
};

struct s_foobar30 {
struct s_foo26 *__s;
};

void foebar16( struct s_foebar16*);
void foe22( struct s_foe22*);
void foo26( struct s_foo26*);
void foobar30( struct s_foobar30*);
void foo49( struct s_foo49*);


//intended output
//In foebar

#include<stdio.h>

int a;

void foo(){
	printf("in global foo!!!\n");
}


void bar(){
	int a;
	
struct s_foebar16 sfoebar16;
sfoebar16.a = &a;


	
struct s_foe22 sfoe22;
sfoe22.a = &a;

foe22(&sfoe22);
}


int main(){

	foo();

	
struct s_foo49 sfoo49;


	foo49(&sfoo49);

	bar();
	return 0;
}


void foebar16( struct s_foebar16* __s ){

		printf("In foebar!!!\n");
	}

void foe22( struct s_foe22* __s ){

	int y, x;
	
struct s_foo26 sfoo26;
sfoo26.__s = __s;
sfoo26.x = &x;
sfoo26.y = &y;

		foo26(&sfoo26);
	}

void foo26( struct s_foo26* __s ){

		printf("in foo inside foe!!!\n");
		
struct s_foobar30 sfoobar30;
sfoobar30.__s = __s;

			foobar30(&sfoobar30);
		}

void foobar30( struct s_foobar30* __s ){

			(*(__s->__s->__s->a));								
			(*(__s->__s->x)) = (*(__s->__s->x)) + 1;
			struct s_foebar16 sfoebar1634;
sfoebar1634.a = __s->__s->__s->a;
foebar16(&sfoebar1634);		
			}

void foo49( struct s_foo49* __s ){

		printf("in foo inside main!!!\n");
	}

