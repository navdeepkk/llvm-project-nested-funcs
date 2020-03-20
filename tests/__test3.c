struct s_label12 {
int* a;
struct sfoo* s;
};

void label12( struct s_label12*);
#include<stdio.h>

int main(){

struct sfoo{
	int x;
	int a[10];
};

	struct sfoo s;
	int a = 1;
	struct s_label12 slabel12;
slabel12.a = &a;
slabel12.s = &s;


	label12(&slabel12);
	return 0;
}


void label12( struct s_label12* __s ){
		(*(__s->s)).x = 2;
		int i;
		for(i = 0;i < 10; i++ ){
			(*(__s->s)).a[i] = (*(__s->a));
		}
		for(i = 0;i < 10; i++ ){
			printf("%d ",(*(__s->s)).a[i]);
		}
	}

