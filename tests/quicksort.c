//intended output
//the array items should be sorted

#include<stdio.h>

void sort () {
		int items[] = {34432,5,43,345,23,4,45,4,31,343,434,43,345};
		int size = sizeof(items)/sizeof(int);
		
		int first, last;
    quickSort: {
				int p, q;
        swap: {
						//printf("swapping %d %d\n", p, q);
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
						//printf("pivotIndex is %d\n", index);
						pivotIndex = index;
        }

        if (first < last) {
            partition();
						int temp = last;
						last = pivotIndex - 1;
						//printf("calling qsort with %d %d\n", first, last);
            quickSort();
						first = pivotIndex + 1;
						last = temp;
						//printf("calling qsort with %d %d\n", first, last);
            quickSort();
        }
    }
		first = 0; 
		last = size - 1;
		//printf("calling qsort with %d %d\n", first, last);
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
