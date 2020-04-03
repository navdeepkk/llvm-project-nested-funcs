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
        foo:{
							bar:{
							if(i == 0){
                for(ij = 0; ij < 2; ij++){
                       a[ij + ij + ij] [ij + ij + ij] [ij +ij +ij] = 5;							//array 'a' is captured from the enclosing scope. array 'b' is global
												b[ij + ij] = ij;																						//and is used for indexing array 'a' further.
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
foo();																																							//call to set elements in array 'a'.
i = 1;
foo();																																							//call to print array 'a'.

        return 0;
}
