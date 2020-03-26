#include<stdio.h>

void hey(){
	struct point{
		int x, y;
	};

	struct point p;
		p.x = 3;
		p.y = 3;
		printf("%d %d\n", p.x, p.y);
	
}

struct point{
			int x, y;
		};

int main(){
	struct point{
			int x, y;
		};
	foo:{		
	struct point{
			int x, y;
		};
		bar:{
			struct point p1;
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}
		foe:{
			struct point p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
		}
	bar();
	foe();
}
	foo();
			struct point p2;
			p2.x = 2;
			p2.y = 2;
			printf("%d %d\n", p2.x, p2.y);
	hey();
	return 0;
}

