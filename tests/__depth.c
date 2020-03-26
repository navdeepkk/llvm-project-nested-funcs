struct s_r9 {
int* a;
};

struct s_p11 {
struct s_r9 *__s;
int* b;
};

struct s_q17 {
struct s_p11 *__s;
int* c;
int* b;
};

struct s_s19 {
struct s_q17 *__s;
int* d;
};



void r9( struct s_r9*);
void p11( struct s_p11*);
void q17( struct s_q17*);
void s19( struct s_s19*);
//intended output
//4 3 2 1 0


#include<stdio.h>

void main(){
    int a;
    struct s_r9 sr9;
sr9.a = &a;


    r9(&sr9);
}



void r9( struct s_r9* __s ){
        int b = 5;
            struct s_p11 sp11;
sp11.__s = __s;
sp11.b = &b;

        p11(&sp11);    
    }

void p11( struct s_p11* __s ){
								static int b = 5;
                b--;
                printf("%d \n", b);
                if(b==0) return;
                int c;
                struct s_q17 sq17;
sq17.__s = __s;
sq17.c = &c;
sq17.b = &b;

                q17(&sq17);
            }

void q17( struct s_q17* __s ){
                    int d;
                    struct s_s19 ss19;
ss19.__s = __s;
ss19.d = &d;

                    s19(&ss19);
                }

void s19( struct s_s19* __s ){
                        p11(__s->__s->__s);
                    }

