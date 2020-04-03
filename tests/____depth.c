


struct s_r9 {

};


struct s_p13 {

struct s_r9 *__s;
int * b;
};


struct s_q21 {

struct s_p13 *__s;
int * c;
int * a;
};


struct s_s25 {

struct s_q21 *__s;
int * d;
};

void r9( struct s_r9*);
void p13( struct s_p13*);
void q21( struct s_q21*);
void s25( struct s_s25*);


//intended output
//4 3 2 1 0


#include<stdio.h>

void main(){
    
struct s_r9 sr9;

    r9(&sr9);
}



void r9( struct s_r9* __s ){

        int b = 5;
            
struct s_p13 sp13;
sp13.__s = __s;
sp13.b = &b;

        p13(&sp13);    
    }

void p13( struct s_p13* __s ){

								int a = 0;
                (*(__s->b))--;
                printf("b:%d a:%d\n",a ,(*(__s->b)));
                if((*(__s->b))==0) return;
                int c;
                
struct s_q21 sq21;
sq21.__s = __s;
sq21.c = &c;
sq21.a = &a;

                q21(&sq21);
            }

void q21( struct s_q21* __s ){

                    int d;
                    
struct s_s25 ss25;
ss25.__s = __s;
ss25.d = &d;

                    s25(&ss25);
                }

void s25( struct s_s25* __s ){

                        p13(__s->__s->__s);
                    }



