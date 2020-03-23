struct s_quickSort7 {
int* last;
int* first;
int* items;
int* size;
};

struct s_partition16 {
struct s_quickSort7 *__s;
int* p;
int* pivotIndex;
int* q;
};

struct s_swap9 {
struct s_quickSort7 *__s;
int* q;
int* p;
};

void quickSort7( struct s_quickSort7*);
void swap9( struct s_swap9*);
void partition16( struct s_partition16*);
#include<stdio.h>

void sort () {
		int items[] = {5, 4, 3, 2, 1};
		int size = 5;
		int first, last;
    struct s_quickSort7 squickSort7;
squickSort7.last = &last;
squickSort7.first = &first;
squickSort7.items = &items;
squickSort7.size = &size;


		first = 0; 
		last = size - 1;
    quickSort7(&squickSort7);

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


void quickSort7( struct s_quickSort7* __s ) {
				int p, q;
        struct s_swap9 sswap9;
sswap9.__s = __s;
sswap9.q = &q;
sswap9.p = &p;


				int pivotIndex; 
        struct s_partition16 spartition16;
spartition16.__s = __s;
spartition16.p = &p;
spartition16.pivotIndex = &pivotIndex;
spartition16.q = &q;


        if ((*(__s->first)) < (*(__s->last))) {
            partition16(&spartition16);
						(*(__s->last)) = pivotIndex - 1;
            quickSort7(__s);
						(*(__s->first)) = pivotIndex + 1; 
            quickSort7(__s);
        }
    }

void swap9( struct s_swap9* __s ) {
            int tmp = (__s->__s->items)[(*(__s->p))];
            (__s->__s->items)[(*(__s->p))] = (__s->__s->items)[(*(__s->q))];
            (__s->__s->items)[(*(__s->q))] = tmp;
        }

void partition16( struct s_partition16* __s ) {
            int pivot = (__s->__s->items)[(*(__s->__s->first))], index = (*(__s->__s->first));
            (*(__s->p)) = index;
						(*(__s->q)) = (*(__s->__s->last));
						struct s_swap9 sswap920;
sswap920.__s = __s->__s;
sswap920.q = __s->q;
sswap920.p = __s->p;
swap9(&sswap920);
						int i;
            for (i = (*(__s->__s->first)); i < (*(__s->__s->last)); i++)
                if ((__s->__s->items)[i] < pivot){
										(*(__s->p)) = index++;
										(*(__s->q)) = i;
                    struct s_swap9 sswap926;
sswap926.__s = __s->__s;
sswap926.q = __s->q;
sswap926.p = __s->p;
swap9(&sswap926);
									}
						(*(__s->p)) = index;	
						(*(__s->q)) = (*(__s->__s->last));
            struct s_swap9 sswap930;
sswap930.__s = __s->__s;
sswap930.q = __s->q;
sswap930.p = __s->p;
swap9(&sswap930);
						(*(__s->pivotIndex)) = index;
        }

