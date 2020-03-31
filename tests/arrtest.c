//intended output
//5 5 5 5 5

#include<stdio.h>

int a[10][5][2];
int b[5];
int main(){
				int ij;
				int i;
        foo:{
							bar:{
							if(i == 0){
                for(ij = 0; ij < 2; ij++){
                       a[ij + ij + ij] [ij + ij + ij] [ij +ij +ij] = 5;
												b[ij + ij] = ij;
                }
							}
							else if(i == 1){
									for(ij = 0; ij < 2; ij++){
									printf("%d ", a[b[ij + ij] + ij + ij] [b[ij + ij] + ij + ij] [b[ij + ij] + ij + ij]);
								}
								printf("\n");	
							}
            }
	bar();
}
i = 0;
foo();

i = 1;
foo();

        return 0;
}
