struct s_foo7 {
int* i;
int* a;
int* ij;
};

void foo7( struct s_foo7*);
#include<stdio.h>

int main(){
        int a[10][10];
				int ij;
				int i;
        struct s_foo7 sfoo7;
sfoo7.i = &i;
sfoo7.a = &a;
sfoo7.ij = &ij;


i = 0;
foo7(&sfoo7);

i = 1;
foo7(&sfoo7);

        return 0;
}


void foo7( struct s_foo7* __s ){
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

