struct s_foo6 {
};

struct s_bar20 {
struct s_foo6 *__s;
struct point9 * p;
};

struct point9{
int a[10];
		
struct loc12{

			int x,y;	
		};
		struct loc12 l;
};

struct point24{

		int a[10];
		int y;	
		
struct loc29{

			int x,y;	
		};
		struct loc29 l;
	};

void foo6( struct s_foo6*);
void bar20( struct s_bar20*);


#include<stdio.h>

int i;
int main(){

struct s_foo6 sfoo6;


foo6(&sfoo6);	
	return 0;
}


void foo6( struct s_foo6* __s ){

		
	
	struct point9 p[5];
	
struct s_bar20 sbar20;
sbar20.__s = __s;
sbar20.p = &p;

bar20(&sbar20);
}

void bar20( struct s_bar20* __s ){

	 struct point9 p[5];	
	 


	struct point24 p1;
	
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

