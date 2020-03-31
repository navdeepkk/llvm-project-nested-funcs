#include <stdio.h>

void fun();

typedef struct {
		int x, y;
	}point;

typedef point pnt;

//typedef float point;

struct location{
	int x,y;
};

typedef struct location loc;

typedef struct xxxx{
	int x, y;
}yes;
 
int main() {
	typedef  int ui;
	ui i[10], j[10];
	loc l;
	struct location l2;
	typedef struct{int x;}point;
	typedef point pnt;
	typedef x;
	x y;	
	point p;
	yes l3;
	int k = 9;
/*
	foo:{
		p.x = 5;
		p.y = 5;
		printf("i = %d\n", i[0]);
		printf("j = %d\n", j[0]);
		printf("k = %d\n", k);
	}
*/
	foo();
	return 0;
}

