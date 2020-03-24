struct s_foo17 {
int * b;
struct s* ss;
struct s * arr;
};

void foo17( struct s_foo17*);
//intended output
//0 1 2 3 4
//1 

#include<stdio.h>

struct s{
	int i;
	int a[5][5];
};


int main(){
	struct s ss;
	struct s arr[5];
	int b[20][20];
	struct s_foo17 sfoo17;
sfoo17.b = &b;
sfoo17.ss = &ss;
sfoo17.arr = &arr;


	foo17(&sfoo17);	
}


void foo17( struct s_foo17* __s ){
			(*(__s->ss)).i = 0;
			for((*(__s->ss)).i = 0; (*(__s->ss)).i < 5; (*(__s->ss)).i++){
				(*(__s->ss)).a[(*(__s->ss)).i][(*(__s->ss)).i] = (*(__s->ss)).i;
				(__s->b)[(*(__s->ss)).i * 20 + (*(__s->ss)).i] = 20;
				//b[5][5] = ss.i;
			}
			
			for((*(__s->ss)).i = 0; (*(__s->ss)).i < 5; (*(__s->ss)).i++){
				printf("%d ",(*(__s->ss)).a[(*(__s->ss)).i][(*(__s->ss)).i]);
				printf("%d ",(__s->b)[(*(__s->ss)).i * 20 + (*(__s->ss)).i]);
			}
			printf("\n");
			
			(__s->arr)[0].i = 1;
			(__s->arr)[0].a[0][0] = (__s->arr)[0].i;
			printf("%d\n ", (__s->arr)[0].a[0][0]);
	}

