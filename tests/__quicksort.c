struct s_quickSort12 {
int * last;
int * first;
int  * items;
int * size;
};

struct s_swap16 {
struct s_quickSort12 *__s;
int * q;
int * p;
};

struct s_partition26 {
struct s_quickSort12 *__s;
int * p;
int * pivotIndex;
int * q;
};

void quickSort12( struct s_quickSort12*);
void swap16( struct s_swap16*);
void partition26( struct s_partition26*);


//intended output
//the array items should be sorted

#include<stdio.h>

void sort () {
		int items[] = {34432,5,43,345,23,4,45,4,31,343,434,43,345};
		int size = sizeof(items)/sizeof(int);
		
		int first, last;
    
struct s_quickSort12 squickSort12;
squickSort12.last = &last;
squickSort12.first = &first;
squickSort12.items = &items;
squickSort12.size = &size;

		first = 0; 
		last = size - 1;
		//printf("calling qsort with %d %d\n", first, last);
    quickSort12(&squickSort12);

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


void quickSort12( struct s_quickSort12* __s ) {

				int p, q;
        
struct s_swap16 sswap16;
sswap16.__s = __s;
sswap16.q = &q;
sswap16.p = &p;


				int pivotIndex; 
        
struct s_partition26 spartition26;
spartition26.__s = __s;
spartition26.p = &p;
spartition26.pivotIndex = &pivotIndex;
spartition26.q = &q;


        if ((*(__s->first)) < (*(__s->last))) {
            partition26(&spartition26);
						int temp = (*(__s->last));
						(*(__s->last)) = pivotIndex - 1;
						//printf("calling qsort with %d %d\n", first, last);
            quickSort12(__s);
						(*(__s->first)) = pivotIndex + 1;
						(*(__s->last)) = temp;
						//printf("calling qsort with %d %d\n", first, last);
            quickSort12(__s);
        }
    }

void swap16( struct s_swap16* __s ) {

						//printf("swapping %d %d\n", p, q);
            int tmp = (__s->__s->items)[(*(__s->p))];
            (__s->__s->items)[(*(__s->p))] = (__s->__s->items)[(*(__s->q))];
            (__s->__s->items)[(*(__s->q))] = tmp;
        }

void partition26( struct s_partition26* __s ) {

            int pivot = (__s->__s->items)[(*(__s->__s->last))], index = (*(__s->__s->first));
            //p = index;
						//q = last;
						//swap();
						int i;
            for (i = (*(__s->__s->first)); i < (*(__s->__s->last)); i++){
                if ((__s->__s->items)[i] <= pivot){
										(*(__s->p)) = index++;
										(*(__s->q)) = i;
                    struct s_swap16 sswap1637;
sswap1637.__s = __s->__s;
sswap1637.q = __s->q;
sswap1637.p = __s->p;
swap16(&sswap1637);
									}
						}
						(*(__s->p)) = index;	
						(*(__s->q)) = (*(__s->__s->last));
            struct s_swap16 sswap1642;
sswap1642.__s = __s->__s;
sswap1642.q = __s->q;
sswap1642.p = __s->p;
swap16(&sswap1642);
						//printf("pivotIndex is %d\n", index);
						(*(__s->pivotIndex)) = index;
        }

