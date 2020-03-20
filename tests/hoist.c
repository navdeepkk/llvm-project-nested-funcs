struct s_r5 {
int* a;
};

struct s_p7 {
struct s_r5 *s;
int* b;
};

struct s_q12 {
struct s_p7 *s;
int* c;
};

struct s_s14 {
struct s_q12 *s;
int* d;
};

void r5( struct s_r5*);
void p7( struct s_p7*);
void q12( struct s_q12*);
void s14( struct s_s14*);
#include<stdio.h>

void main(){
    int a;
    struct s_r5 sr5;
sr5.a = &a;
r5:{
        int b = 5;
            struct s_p7 sp7;
sp7.s = s;
sp7.b = &b;
p7:{
                (*(s->b))--;
                printf("%d \n", (*(s->b)));
                if((*(s->b))==0) return;
                int c;
                struct s_q12 sq12;
sq12.s = s;
sq12.c = &c;
q12:{
                    int d;
                    struct s_s14 ss14;
ss14.s = s;
ss14.d = &d;
s14:{
                        p7(s->s->s);
                    }
                    s14(&ss14);
                }
                q12(&sq12);
            }
        p7(&sp7);    
    }
    r5(&sr5);
    return;
}

