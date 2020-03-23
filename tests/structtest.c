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
	foo:{
			ss.i = 0;
			for(ss.i = 0; ss.i < 5; ss.i++){
				ss.a[ss.i] = ss.i;
			}
			
			for(ss.i = 0; ss.i < 5; ss.i++){
				printf("%d ",ss.i);
			}
			printf("\n");
			
			arr[0].i = 1;
			arr[0].a[0] = arr[0].i;
			printf("%d\n ", arr[0].a[0]);
	}
	foo();	
}
