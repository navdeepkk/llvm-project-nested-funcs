struct point4{
		char *name;
	
		struct loc{
			int x,y;	
		};

		struct loc l;
};


#include<stdio.h>

int main(){
	struct point4{
		char *name;
	
		struct loc{
			int x,y;	
		};

		struct loc l;
};

struct point4 p1;
p1.name = "p1";
p1.l.x = 1;
p1.l.y = 2;
	
	return 0;
}
