struct s_r5 {
int* a;
};

struct s_p7 {
struct s_r5 *__s;
int* b;
};

struct s_q13 {
struct s_p7 *__s;
int* c;
int* b;
};

struct s_s15 {
struct s_q13 *__s;
int* d;
};

void r5( struct s_r5*);
void p7( struct s_p7*);
void q13( struct s_q13*);
void s15( struct s_s15*);
#include<stdio.h>

void main(){
    int a;
    struct s_r5 sr5;
sr5.a = &a;


    r5(&sr5);
    return;
}



void r5( struct s_r5* __s ){
        int b = 5;
            struct s_p7 sp7;
sp7.__s = __s;
sp7.b = &b;

        p7(&sp7);    
    }

void p7( struct s_p7* __s ){
								static int b = 5;
                b--;
                printf("%d \n", b);
                if(b==0) return;
                int c;
                struct s_q13 sq13;
sq13.__s = __s;
sq13.c = &c;
sq13.b = &b;

                q13(&sq13);
            }

void q13( struct s_q13* __s ){
                    int d;
                    struct s_s15 ss15;
ss15.__s = __s;
ss15.d = &d;

                    s15(&ss15);
                }

void s15( struct s_s15* __s ){
                        p7(__s->__s->__s);
                    }

