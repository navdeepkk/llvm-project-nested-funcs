struct s_foo10 {
int* i;
int * a;
int* ij;
};

void foo10( struct s_foo10*);
//intended output
//5 5 5 5 5

#include<stdio.h>

int main(){
        int a[10][10];
				int ij;
				int i;
        struct s_foo10 sfoo10;
sfoo10.i = &i;
sfoo10.a = &a;
sfoo10.ij = &ij;


i = 0;
foo10(&sfoo10);

i = 1;
foo10(&sfoo10);

        return 0;
}


void foo10( struct s_foo10* __s ){
							if((*(__s->i)) == 0){
                for((*(__s->ij)) = 0; (*(__s->ij)) < 5; (*(__s->ij))++){
                        (__s->a)[(*(__s->ij)) * 10 + (*(__s->ij))] = 5;
                }
							}
							else if((*(__s->i)) == 1){
									for((*(__s->ij)) = 0; (*(__s->ij)) < 5; (*(__s->ij))++){
									printf("%d ", (__s->a)[(*(__s->ij)) * 10 + (*(__s->ij))]);
									printf("\n");
								}
							}
            }

