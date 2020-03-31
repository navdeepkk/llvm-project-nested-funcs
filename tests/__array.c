struct s_f136 {
int * k;
int * l;
int * j;
int  * a;
int * i;
};

struct s_print42 {
struct s_f136 *__s;
int * p;
int  * b;
};

void f136( struct s_f136*);
void print42( struct s_print42*);


/*
Expected output:
0 0 0 0 0 0 
0 1 0 0 0 0 
0 0 2 0 0 0 
0 0 0 0 0 0 
0 0 0 0 4 0 
0 0 0 0 0 0 

 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 

 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 

*/


#include<stdio.h>

int main()
{
		  int a[5] = {0,1,2,0,4};
		  int i,j,k,l;

struct s_f136 sf136;
sf136.k = &k;
sf136.l = &l;
sf136.j = &j;
sf136.a = &a;
sf136.i = &i;



	f136(&sf136);

}



void f136( struct s_f136* __s ){

			  int b[3][6][6];
				int p;

			
struct s_print42 sprint42;
sprint42.__s = __s;
sprint42.p = &p;
sprint42.b = &b;

				
				//Initialize
				p = 0;
				print42(&sprint42);
			

			  for((*(__s->i))=0;(*(__s->i))<5;(*(__s->i))++)
			  {
						 b[0][(__s->a)[(*(__s->i))]][(__s->a)[(*(__s->i))]] = (__s->a)[(*(__s->i))];
			  }
				
			p = 1;	
				print42(&sprint42);

	}

void print42( struct s_print42* __s ){

				for((*(__s->__s->j))=0;(*(__s->__s->j))<3;(*(__s->__s->j))++)
				{
					for((*(__s->__s->k))=0;(*(__s->__s->k))<6;(*(__s->__s->k))++)
					{
						for((*(__s->__s->l))=0;(*(__s->__s->l))<6;(*(__s->__s->l))++)
						{
							if((*(__s->p)) == 1)
							printf("%d ",(__s->b)[(*(__s->__s->j)) * 6 * 6 + (*(__s->__s->k)) * 6 + (*(__s->__s->l))]);
							else
							(__s->b)[(*(__s->__s->j)) * 6 * 6 + (*(__s->__s->k)) * 6 + (*(__s->__s->l))] = 0;
						}
						printf("\n");
					}
				
					printf("\n \n");
				}
			}

