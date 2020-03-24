struct s_quickSort11 {
int* last;
int* first;
int * items;
int* size;
};

struct s_partition21 {
struct s_quickSort11 *__s;
int* p;
int* pivotIndex;
int* q;
};

struct s_swap13 {
struct s_quickSort11 *__s;
int* q;
int* p;
};

void quickSort11( struct s_quickSort11*);
void swap13( struct s_swap13*);
void partition21( struct s_partition21*);
//intended output
//the array items should be sorted

#include<stdio.h>

void sort () {
		int items[] = {34432,5,43,345,23,4,45,4,31,343,434,43,345};
		int size = sizeof(items)/sizeof(int);
		
		int first, last;
    struct s_quickSort11 squickSort11;
squickSort11.last = &last;
squickSort11.first = &first;
squickSort11.items = &items;
squickSort11.size = &size;


		first = 0; 
		last = size - 1;
		//printf("calling qsort with %d %d\n", first, last);
    quickSort11(&squickSort11);

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


void quickSort11( struct s_quickSort11* __s ) {
				int p, q;
        struct s_swap13 sswap13;
sswap13.__s = __s;
sswap13.q = &q;
sswap13.p = &p;


				int pivotIndex; 
        struct s_partition21 spartition21;
spartition21.__s = __s;
spartition21.p = &p;
spartition21.pivotIndex = &pivotIndex;
spartition21.q = &q;


        if ((*(__s->first)) < (*(__s->last))) {
            partition21(&spartition21);
						int temp = (*(__s->last));
						(*(__s->last)) = pivotIndex - 1;
						//printf("calling qsort with %d %d\n", first, last);
            quickSort11(__s);
						(*(__s->first)) = pivotIndex + 1;
						(*(__s->last)) = temp;
						//printf("calling qsort with %d %d\n", first, last);
            quickSort11(__s);
        }
    }

void swap13( struct s_swap13* __s ) {
						//printf("swapping %d %d\n", p, q);
            int tmp = (__s->__s->items)[(*(__s->p))];
            (__s->__s->items)[(*(__s->p))] = (__s->__s->items)[(*(__s->q))];
            (__s->__s->items)[(*(__s->q))] = tmp;
        }

void partition21( struct s_partition21* __s ) {
            int pivot = (__s->__s->items)[(*(__s->__s->last))], index = (*(__s->__s->first));
            //p = index;
						//q = last;
						//swap();
						int i;
            for (i = (*(__s->__s->first)); i < (*(__s->__s->last)); i++){
                if ((__s->__s->items)[i] <= pivot){
										(*(__s->p)) = index++;
										(*(__s->q)) = i;
                    struct s_swap13 sswap1331;
sswap1331.__s = __s->__s;
sswap1331.q = __s->q;
sswap1331.p = __s->p;
swap13(&sswap1331);
									}
						}
						(*(__s->p)) = index;	
						(*(__s->q)) = (*(__s->__s->last));
            struct s_swap13 sswap1336;
sswap1336.__s = __s->__s;
sswap1336.q = __s->q;
sswap1336.p = __s->p;
swap13(&sswap1336);
						//printf("pivotIndex is %d\n", index);
						(*(__s->pivotIndex)) = index;
        }

