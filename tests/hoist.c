struct s_label7 {
struct point4 * p2;
struct point4 * p1;
};

struct s_foo19 {
struct s_label7 *__s;
const int * x;
const struct point  * p4;
const  struct point8 * p6;
struct point8 * p7;
struct point8 * p1;
struct point8 * p5;
struct point8 * p8;
};

struct point8{
			int x, y;
			struct loc10{
				int x;
			}l1,l2[10];
			struct loc10 l3,l4;
		};

struct point4{
	int x, y;
};

void label7( struct s_label7*);
void foo19( struct s_foo19*);


//#include<stdio.h>

int main(){
struct point4{
	int x, y;
}p1, p2;
struct s_label7 slabel7;
slabel7.p2 = &p2;
slabel7.p1 = &p1;
label7:{
		struct point8{
			int x, y;
			struct loc10{
				int x;
			}l1,l2[10];
			struct loc10 l3,l4;
		}p1;

		const struct point8 p4[10], p6;
		struct point8 p5[10][10], p7[10], p8[10];
		const int x;
		struct s_foo19 sfoo19;
sfoo19.__s = __s;
sfoo19.x = &x;
sfoo19.p4 = &p4;
sfoo19.p6 = &p6;
sfoo19.p7 = &p7;
sfoo19.p1 = &p1;
sfoo19.p5 = &p5;
sfoo19.p8 = &p8;
foo19:{

		}
	}
	
	label7(&slabel7);

return 0;
}

