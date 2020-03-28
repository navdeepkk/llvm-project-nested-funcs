#include<stdio.h>

int i;
int main(){
foo:{
		struct point{int a[10];
		struct loc{
			int x,y;	
		};
		struct loc l;
};	
	struct point p[5];
	bar:{
	 struct point p[5];	
	 struct point{
		int a[10];
		int y;	
		struct loc{
			int x,y;	
		};
		struct loc l;
	};

	struct point p1;
	
	//struct point p[5];

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
bar();
}

foo();	
	return 0;
}
