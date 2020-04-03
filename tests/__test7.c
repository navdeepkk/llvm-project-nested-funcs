struct s_label15 {
struct point6 * p2;
struct point6 * p1;
};

struct s_foo37 {
struct s_label15 *__s;
const int * x;
const struct point  * p4;
const  struct point19 * p6;
struct point19 * p7;
struct point19 * p1;
struct point19 * p5;
struct point19 * p8;
};

struct point19{

			int x, y;
			
struct loc23{

				int x;
			}l1,l2[10];
			
			struct loc23 l3,l4;
		};

struct point6{

	int x, y;
};

void label15( struct s_label15*);
void foo37( struct s_foo37*);


#include<stdio.h>

int main(){



struct point6 p1;

struct point6 p2;
	

struct s_label15 slabel15;
slabel15.p2 = &p2;
slabel15.p1 = &p1;

	
	label15(&slabel15);

return 0;
}


void label15( struct s_label15* __s ){

		


struct point19 p1;

		const struct point19 p4[10], p6;
		struct point19 p5[10][10], p7[10], p8[10];
		const int x;

	
struct s_foo37 sfoo37;
sfoo37.__s = __s;
sfoo37.x = &x;
sfoo37.p4 = &p4;
sfoo37.p6 = &p6;
sfoo37.p7 = &p7;
sfoo37.p1 = &p1;
sfoo37.p5 = &p5;
sfoo37.p8 = &p8;

	foo37(&sfoo37);
	}

void foo37( struct s_foo37* __s ){


		}

