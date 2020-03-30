#include <stdio.h>

typedef struct {
		int x, y;
	}point;

typedef point x;

 
int main() {
	typedef unsigned int ui;
	ui i[10], j[10];
	int k = 9;
	
	point p;
	foo:{
		p.x = 5;
		p.y = 5;
		//printf("i = %d\n", i);
		//printf("j = %d\n", j);
		//iprintf("k = %d\n", k);
	}
	foo();
	return 0;
}

