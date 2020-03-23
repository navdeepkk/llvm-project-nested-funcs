struct s_foe14 {
int* a;
};

struct s_foebar10 {
int* a;
};

struct s_foo16 {
struct s_foe14 *__s;
int* x;
int* y;
};

struct s_foobar17 {
struct s_foo16 *__s;
};

void foebar10( struct s_foebar10*);
void foe14( struct s_foe14*);
void foo16( struct s_foo16*);
void foobar17( struct s_foobar17*);
//intended output
//In foebar

#include<stdio.h>

int a;

void bar(){
	int a;
	struct s_foebar10 sfoebar10;
sfoebar10.a = &a;



	struct s_foe14 sfoe14;
sfoe14.a = &a;


foe14(&sfoe14);
}


int main(){
bar();
return 0;
}


void foebar10( struct s_foebar10* __s ){
		printf("In foebar!!!\n");
	}

void foe14( struct s_foe14* __s ){
	int y, x;
	struct s_foo16 sfoo16;
sfoo16.__s = __s;
sfoo16.x = &x;
sfoo16.y = &y;

		foo16(&sfoo16);
	}

void foo16( struct s_foo16* __s ){
		struct s_foobar17 sfoobar17;
sfoobar17.__s = __s;

			foobar17(&sfoobar17);
		}

void foobar17( struct s_foobar17* __s ){
			(*(__s->__s->__s->a));								
			(*(__s->__s->x)) = (*(__s->__s->x)) + 1;
			struct s_foebar10 sfoebar1020;
sfoebar1020.a = __s->__s->__s->a;
foebar10(&sfoebar1020);		
			}

