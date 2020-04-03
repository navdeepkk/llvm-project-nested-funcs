struct s_foo22 {
int  * a;
int * ij;
int * i;
};

struct s_bar25 {
struct s_foo22 *__s;
};

void foo22( struct s_foo22*);
void bar25( struct s_bar25*);


//------------------------------------------//
// This test case shows that arrays of any  //
// dimensions are supported along with and  //
// may be captured from any scope and also  //
// they may be indexed with any variable    //
// within its scope or from scopes captured //
// from enclosing blocks. in first call to  //
// foo it sets the elements of the array 'a'//
// and in second calls it prints out those  //
// elements.																//
// EXPECTED OUTPUT													//
// 5 5																			//
//------------------------------------------//
#include<stdio.h>

int b[5];
int main(){
				int ij;
				int i;
				int a[10][5][2];
        
struct s_foo22 sfoo22;
sfoo22.a = &a;
sfoo22.ij = &ij;
sfoo22.i = &i;

i = 0;
foo22(&sfoo22);																																							//call to set elements in array 'a'.
i = 1;
foo22(&sfoo22);																																							//call to print array 'a'.

        return 0;
}


void foo22( struct s_foo22* __s ){

							
struct s_bar25 sbar25;
sbar25.__s = __s;

	bar25(&sbar25);
}

void bar25( struct s_bar25* __s ){

							if((*(__s->__s->i)) == 0){
                for((*(__s->__s->ij)) = 0; (*(__s->__s->ij)) < 2; (*(__s->__s->ij))++){
                       (__s->__s->a)[(*(__s->__s->ij)) + (*(__s->__s->ij)) + (*(__s->__s->ij)) * 5 * 2 +  (*(__s->__s->ij)) + (*(__s->__s->ij)) + (*(__s->__s->ij)) * 2 +  (*(__s->__s->ij)) +(*(__s->__s->ij)) +(*(__s->__s->ij))] = 5;							//array 'a' is captured from the enclosing scope. array 'b' is global
												b[(*(__s->__s->ij)) + (*(__s->__s->ij))] = (*(__s->__s->ij));																						//and is used for indexing array 'a' further.
                }
							}
							else if((*(__s->__s->i)) == 1){
									for((*(__s->__s->ij)) = 0; (*(__s->__s->ij)) < 2; (*(__s->__s->ij))++){
									printf("%d ", (__s->__s->a)[b[(*(__s->__s->ij)) + (*(__s->__s->ij))] + (*(__s->__s->ij)) + (*(__s->__s->ij)) * 5 * 2 +  b[(*(__s->__s->ij)) + (*(__s->__s->ij))] + (*(__s->__s->ij)) + (*(__s->__s->ij)) * 2 +  b[(*(__s->__s->ij)) + (*(__s->__s->ij))] + (*(__s->__s->ij)) + (*(__s->__s->ij))]);
								}
								printf("\n");	
							}
            }

