struct s_quickSort20 {
int * last;
int * first;
int  * items;
int * size;
};

struct s_partition33 {
struct s_quickSort20 *__s;
int * p;
int * pivotIndex;
int * q;
};

struct s_swap24 {
struct s_quickSort20 *__s;
int * q;
int * p;
};

void quickSort20( struct s_quickSort20*);
void swap24( struct s_swap24*);
void partition33( struct s_partition33*);


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
    
struct s_quickSort20 squickSort20;
squickSort20.last = &last;
squickSort20.first = &first;
squickSort20.items = &items;
squickSort20.size = &size;

		first = 0; 
		last = size - 1;
    quickSort20(&squickSort20);

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


void quickSort20( struct s_quickSort20* __s ) {

				int p, q;
        
struct s_swap24 sswap24;
sswap24.__s = __s;
sswap24.q = &q;
sswap24.p = &p;


				int pivotIndex; 
        
struct s_partition33 spartition33;
spartition33.__s = __s;
spartition33.p = &p;
spartition33.pivotIndex = &pivotIndex;
spartition33.q = &q;


        if ((*(__s->first)) < (*(__s->last))) {
            partition33(&spartition33);
						int temp = (*(__s->last));
						(*(__s->last)) = pivotIndex - 1;
            quickSort20(__s);
						(*(__s->first)) = pivotIndex + 1;
						(*(__s->last)) = temp;
            quickSort20(__s);
        }
    }

void swap24( struct s_swap24* __s ) {

            int tmp = (__s->__s->items)[(*(__s->p))];
            (__s->__s->items)[(*(__s->p))] = (__s->__s->items)[(*(__s->q))];
            (__s->__s->items)[(*(__s->q))] = tmp;
        }

void partition33( struct s_partition33* __s ) {

            int pivot = (__s->__s->items)[(*(__s->__s->last))], index = (*(__s->__s->first));
            //p = index;
						//q = last;
						//swap();
						int i;
            for (i = (*(__s->__s->first)); i < (*(__s->__s->last)); i++){
                if ((__s->__s->items)[i] <= pivot){
										(*(__s->p)) = index++;
										(*(__s->q)) = i;
                    struct s_swap24 sswap2444;
sswap2444.__s = __s->__s;
sswap2444.q = __s->q;
sswap2444.p = __s->p;
swap24(&sswap2444);
									}
						}
						(*(__s->p)) = index;	
						(*(__s->q)) = (*(__s->__s->last));
            struct s_swap24 sswap2449;
sswap2449.__s = __s->__s;
sswap2449.q = __s->q;
sswap2449.p = __s->p;
swap24(&sswap2449);
						(*(__s->pivotIndex)) = index;
        }

