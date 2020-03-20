#include<stdio.h>

int main(){

struct sfoo{
	int x;
	int a[10];
};

	struct sfoo s;
	int a = 1;
	label:{
		s.x = 2;
		int i;
		for(i = 0;i < 10; i++ ){
			s.a[i] = a;
		}
		for(i = 0;i < 10; i++ ){
			printf("%d ",s.a[i]);
		}
	}
	label();
	return 0;
}
