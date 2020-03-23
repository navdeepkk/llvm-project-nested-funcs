//intended output
//5 5 5 5 5

#include<stdio.h>

int main(){
        int a[10][10];
				int ij;
				int i;
        foo:{
							if(i == 0){
                for(ij = 0; ij < 5; ij++){
                        a[ij][ij] = 5;
                }
							}
							else if(i == 1){
									for(ij = 0; ij < 5; ij++){
									printf("%d ", a[ij][ij]);
									printf("\n");
								}
							}
            }
i = 0;
foo();

i = 1;
foo();

        return 0;
}
