struct s_foo20 {
int  * b;
};

void foo20( struct s_foo20*);


//intended output
//0 1 2 3 4
//1 

#include<stdio.h>


struct s{

	int i;
	int a[5][5];
};

	struct s ss;
	struct s arr[5];

int main(){
	int b[20][20];
	
struct s_foo20 sfoo20;
sfoo20.b = &b;

	foo20(&sfoo20);	
}


void foo20( struct s_foo20* __s ){

			ss.i = 0;
			for(ss.i = 0; ss.i < 5; ss.i++){
				ss.a[ss.i][ss.i] = ss.i;
				(__s->b)[ss.i * 20 + ss.i] = 20;
				//b[5][5] = ss.i;
			}
			
			for(ss.i = 0; ss.i < 5; ss.i++){
				printf("%d ",ss.a[ss.i][ss.i]);
				printf("%d ",(__s->b)[ss.i * 20 + ss.i]);
			}
			printf("\n");
			
			arr[0].i = 1;
			arr[0].a[0][0] = arr[0].i;
			printf("%d\n ", arr[0].a[0][0]);
	}

