//------------------------------------------//
// This is a working example of quicksort   //
// which takes input the array items, and 	//
// prints it out sorted. This example demos //
// strates the support for recursion, arrays//
// and also shows call resoltion is working //
// as expected.                             //
// EXPECTED OUTPUT                          //
// array items is sorted order.             //
//------------------------------------------//

#include<stdio.h>

void sort () {
		int items[] = {34432,5,43,345,23,4,45,4,31,343,434,43,345};
		int size = sizeof(items)/sizeof(int);
		
		int first, last;
    quickSort: {
				int p, q;
        swap: {
            int tmp = items[p];
            items[p] = items[q];
            items[q] = tmp;
        }

				int pivotIndex; 
        partition: {
            int pivot = items[last], index = first;
            //p = index;
						//q = last;
						//swap();
						int i;
            for (i = first; i < last; i++){
                if (items[i] <= pivot){
										p = index++;
										q = i;
                    swap();
									}
						}
						p = index;	
						q = last;
            swap();
						pivotIndex = index;
        }

        if (first < last) {
            partition();
						int temp = last;
						last = pivotIndex - 1;
            quickSort();
						first = pivotIndex + 1;
						last = temp;
            quickSort();
        }
    }
		first = 0; 
		last = size - 1;
    quickSort();

		int i;
		for(i = 0; i < size; i++){
				printf("%d ", items[i]);
		}
		printf("\n");
}

int main(){
	sort();
	return 0;
}
