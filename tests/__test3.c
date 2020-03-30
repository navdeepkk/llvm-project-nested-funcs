struct s_foo5 {
};

struct s_q14 {
struct s_foo5 *__s;
int * i;
};

struct s_p8 {
struct s_foo5 *__s;
};

struct s_r17 {
struct s_q14 *__s;
};

struct s_s20 {
struct s_r17 *__s;
};

void foo5( struct s_foo5*);
void p8( struct s_p8*);
void q14( struct s_q14*);
void r17( struct s_r17*);
void s20( struct s_s20*);


#include<stdio.h>

int main(){
	
struct s_foo5 sfoo5;

	return 0;
}


void foo5( struct s_foo5* __s ){

		
struct s_p8 sp8;
sp8.__s = __s;

	int i;
	
struct s_q14 sq14;
sq14.__s = __s;
sq14.i = &i;

q14(&sq14);
}

void p8( struct s_p8* __s ){

			int i;
		}

void q14( struct s_q14* __s ){

		
struct s_r17 sr17;
sr17.__s = __s;

		struct s_p8 sp827;
sp827.__s = __s->__s;
p8(&sp827);
		r17(&sr17);
		}

void r17( struct s_r17* __s ){

				
struct s_s20 ss20;
ss20.__s = __s;

				struct s_p8 sp824;
sp824.__s = __s->__s->__s;
p8(&sp824);
				s20(&ss20);
			}

void s20( struct s_s20* __s ){

					struct s_p8 sp822;
sp822.__s = __s->__s->__s->__s;
p8(&sp822);
				}

