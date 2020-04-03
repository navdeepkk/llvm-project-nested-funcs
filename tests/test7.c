#include<stdio.h>

int main(){
struct point{
	int x, y;
}p1, p2;
	
label:{
		struct point{
			int x, y;
			struct loc{
				int x;
			}l1,l2[10];
			
			struct loc l3,l4;
		}p1;

		const struct point p4[10], p6;
		struct point p5[10][10], p7[10], p8[10];
		const int x;

	foo:{

		}
	foo();
	}
	
	label();

return 0;
}
