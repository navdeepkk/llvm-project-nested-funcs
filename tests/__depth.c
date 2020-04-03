struct s_r20 {
};

struct s_p24 {
struct s_r20 *__s;
int * b;
};

struct s_q32 {
struct s_p24 *__s;
int * c;
int * a;
};

struct s_s36 {
struct s_q32 *__s;
int * d;
};

void r20( struct s_r20*);
void p24( struct s_p24*);
void q32( struct s_q32*);
void s36( struct s_s36*);


//------------------------------------------//
// This test case show a case of Indirect   //
// recursion between functions at arbitrary //
// depths. The innermost function can call  //
// any of the functions that are in its     //
// scope    
// 
// EXPECTED OUTPUT													//
// b:4 a:0                                  //
// b:3 a:0                                  //
// b:2 a:0                                  //
// b:1 a:0                                  //
// b:0 a:0                                  //
//------------------------------------------//

#include<stdio.h>

int main(){
    
struct s_r20 sr20;

    r20(&sr20);
return 0;
}



void r20( struct s_r20* __s ){

        int b = 5;
            
struct s_p24 sp24;
sp24.__s = __s;
sp24.b = &b;

        p24(&sp24);    
    }

void p24( struct s_p24* __s ){

								int a = 0;
                (*(__s->b))--;
                printf("b:%d a:%d\n",(*(__s->b)) ,a);
                if((*(__s->b))==0) return;
                int c;
                
struct s_q32 sq32;
sq32.__s = __s;
sq32.c = &c;
sq32.a = &a;

                q32(&sq32);
            }

void q32( struct s_q32* __s ){

                    int d;
                    
struct s_s36 ss36;
ss36.__s = __s;
ss36.d = &d;

                    s36(&ss36);
                }

void s36( struct s_s36* __s ){

                        p24(__s->__s->__s);								//calls p at which is defined outside s.
                    }

