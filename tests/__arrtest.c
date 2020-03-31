struct s_foo12 {
int * i;
int * ij;
};

struct s_bar15 {
struct s_foo12 *__s;
};

void foo12( struct s_foo12*);
void bar15( struct s_bar15*);


//intended output
//5 5 5 5 5

#include<stdio.h>

int a[10][5][2];
int b[5];
int main(){
				int ij;
				int i;
        
struct s_foo12 sfoo12;
sfoo12.i = &i;
sfoo12.ij = &ij;

i = 0;
foo12(&sfoo12);

i = 1;
foo12(&sfoo12);

        return 0;
}


void foo12( struct s_foo12* __s ){

							
struct s_bar15 sbar15;
sbar15.__s = __s;

	bar15(&sbar15);
}

void bar15( struct s_bar15* __s ){

							if((*(__s->__s->i)) == 0){
                for((*(__s->__s->ij)) = 0; (*(__s->__s->ij)) < 2; (*(__s->__s->ij))++){
                       a[(*(__s->__s->ij)) + (*(__s->__s->ij)) + (*(__s->__s->ij))] [(*(__s->__s->ij)) + (*(__s->__s->ij)) + (*(__s->__s->ij))] [(*(__s->__s->ij)) +(*(__s->__s->ij)) +(*(__s->__s->ij))] = 5;
												b[(*(__s->__s->ij)) + (*(__s->__s->ij))] = (*(__s->__s->ij));
                }
							}
							else if((*(__s->__s->i)) == 1){
									for((*(__s->__s->ij)) = 0; (*(__s->__s->ij)) < 2; (*(__s->__s->ij))++){
									printf("%d ", a[b[(*(__s->__s->ij)) + (*(__s->__s->ij))] + (*(__s->__s->ij)) + (*(__s->__s->ij))] [b[(*(__s->__s->ij)) + (*(__s->__s->ij))] + (*(__s->__s->ij)) + (*(__s->__s->ij))] [b[(*(__s->__s->ij)) + (*(__s->__s->ij))] + (*(__s->__s->ij)) + (*(__s->__s->ij))]);
								}
								printf("\n");	
							}
            }

