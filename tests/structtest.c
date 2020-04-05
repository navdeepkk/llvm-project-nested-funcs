//------------------------------------------//
// This exapmle demostrates structures conta//
// arrays, and also arrays of structures.   //
// the array in struct s arr is being assi  //
// gned values in the first for loop and in	//
// second iteration it prints out the assign//
// values. in the third segment the array of//
// structures is assigned values and then th//
// ey are printed. the example also show use//
// of storage classes such as static for var//
// iables in particular the array b here.	  //
// EXPECTED OUTPUT													// 
// 0 20 1 20 2 20 3 20 4 20									//
// 1																				//
//------------------------------------------//

#include<stdio.h>

struct s{
	int i;
	int a[5][5];
};

struct s ss, arr[5];

int main(){
	static int b[20][20];																					//use with storage class static.
	const struct s ss2; 
	foo:{
			ss.i = 0;
			for(ss.i = 0; ss.i < 5; ss.i++){
				ss.a[ss.i][ss.i] = ss.i;																//initializes array 'ss' which.
				b[ss.i][ss.i] = 20;
			}
			
			for(ss.i = 0; ss.i < 5; ss.i++){
				printf("%d ",ss.a[ss.i][ss.i]);													//prints out array 'ss'.
				printf("%d ",b[ss.i][ss.i]);
			}
			printf("\n");
			
			arr[0].i = 1;
			arr[0].a[0][0] = arr[0].i;
			printf("%d\n ", arr[0].a[0][0]);													//array arr is an array of structures which is
	}																															//initialized and then printed.
	foo();	
}
