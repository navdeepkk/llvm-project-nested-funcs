struct s_foo7 {
};

struct s_bar23 {
struct s_foo7 *__s;
};

struct point8{
		int a[10];
	
		struct loc11{
			int x,y;	
		};

		struct loc215{
			struct loc11 l;
		};

		struct loc11 l;
};


void foo7( struct s_foo7*);
void bar23( struct s_bar23*);
#include<stdio.h>

int i;
int main(){


struct s_foo7 sfoo7;



foo7(&sfoo7);	
	return 0;
}


void foo7( struct s_foo7* __s ){
	


	
	struct s_bar23 sbar23;
sbar23.__s = __s;

bar23(&sbar23);
}

void bar23( struct s_bar23* __s ){
	/*
	 struct point{
		int a[10];
		int y;	
		struct loc{
			int x,y;	
		};
		struct loc l;
};
	*/


	struct point8 p1;
	
	struct point8 p[5];

	for( i = 0 ; i < 5 ; i++){
			p1.a[i] = i;
			p[i].a[i] = i;
		}
	p1.l.x = 1;
	p1.l.y = 2;
	printf("%d %d \n",p1.l.x, p1.l.y );
	
	for( i = 0 ; i < 5 ; i++){
			printf("%d %d ",p1.a[i], p[i].a[i]);
		}
	printf("\n");	
}

