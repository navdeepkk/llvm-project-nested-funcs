struct s_foo11 {
int * i;
int  * a;
int * ij;
};

void foo11( struct s_foo11*);


//intended output
//5 5 5 5 5

#include<stdio.h>

int main(){
        int a[10][10];
				int ij;
				int i;
        
struct s_foo11 sfoo11;
sfoo11.i = &i;
sfoo11.a = &a;
sfoo11.ij = &ij;

i = 0;
foo11(&sfoo11);

i = 1;
foo11(&sfoo11);

        return 0;
}


void foo11( struct s_foo11* __s ){

							if((*(__s->i)) == 0){
                for((*(__s->ij)) = 0; (*(__s->ij)) < 5; (*(__s->ij))++){
                        (__s->a)[(*(__s->ij)) * 10 + 			(*(__s->ij))] = 5;
                }
							}
							else if((*(__s->i)) == 1){
									for((*(__s->ij)) = 0; (*(__s->ij)) < 5; (*(__s->ij))++){
									printf("%d ", (__s->a)[(*(__s->ij)) * 10 + (*(__s->ij))]);
									printf("\n");
								}
							}
            }

