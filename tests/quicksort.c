//intended output
//the array items should be sorted

#include<stdio.h>

void sort () {
		int items[] = {5, 4, 3, 2, 1};
		int size = 5;
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
            int pivot = items[first], index = first;
            p = index;
						q = last;
						swap();
						int i;
            for (i = first; i < last; i++)
                if (items[i] < pivot){
										p = index++;
										q = i;
                    swap();
									}
						p = index;	
						q = last;
            swap();
						pivotIndex = index;
        }

        if (first < last) {
            partition();
						last = pivotIndex - 1;
            quickSort();
						first = pivotIndex + 1; 
            quickSort();
        }
    }
		first = 0; 
		last = size - 1;
    quickSort();

		int i;
		for(int i = 0; i < size; i++){
				printf("%d ", items[i]);
		}
		printf("\n");
}

int main(){
	sort();
	return 0;
}
