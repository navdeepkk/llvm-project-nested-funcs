struct s_foo16 {
struct s * arr;
struct s* ss;
};

void foo16( struct s_foo16*);
//intended output
//0 1 2 3 4
//1 

#include<stdio.h>

struct s{
	int i;
	int a[5];
};


int main(){
	struct s ss;
	struct s arr[5];
	struct s_foo16 sfoo16;
sfoo16.arr = &arr;
sfoo16.ss = &ss;


	foo16(&sfoo16);	
}


void foo16( struct s_foo16* __s ){
			(*(__s->ss)).i = 0;
			for((*(__s->ss)).i = 0; (*(__s->ss)).i < 5; (*(__s->ss)).i++){
				(*(__s->ss)).a[(*(__s->ss)).i] = (*(__s->ss)).i;
			}
			
			for((*(__s->ss)).i = 0; (*(__s->ss)).i < 5; (*(__s->ss)).i++){
				printf("%d ",(*(__s->ss)).i);
			}
			printf("\n");
			
			(__s->arr)[0].i = 1;
			(__s->arr)[0].a[0] = (__s->arr)[0].i;
			printf("%d\n ", (__s->arr)[0].a[0]);
	}

