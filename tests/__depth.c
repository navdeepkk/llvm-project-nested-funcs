struct s_r19 {
};

struct s_p23 {
struct s_r19 *__s;
int * b;
};

struct s_q31 {
struct s_p23 *__s;
int * c;
int * a;
};

struct s_s35 {
struct s_q31 *__s;
int * d;
};

void r19( struct s_r19*);
void p23( struct s_p23*);
void q31( struct s_q31*);
void s35( struct s_s35*);


//------------------------------------------//
// This test case show a case of Indirect   //
// recursion between functions at arbitrary //
// depths. The innermost function can call  //
// any of the functions that are in its     //
// scope.                                   //
// EXPECTED OUTPUT													//
// b:4 a:0                                  //
// b:3 a:0                                  //
// b:2 a:0                                  //
// b:1 a:0                                  //
// b:0 a:0                                  //
//------------------------------------------//

#include<stdio.h>

int main(){
    
struct s_r19 sr19;

    r19(&sr19);
return 0;
}



void r19( struct s_r19* __s ){

        int b = 5;
            
struct s_p23 sp23;
sp23.__s = __s;
sp23.b = &b;

        p23(&sp23);    
    }

void p23( struct s_p23* __s ){

								int a = 0;
                (*(__s->b))--;
                printf("b:%d a:%d\n",(*(__s->b)) ,a);
                if((*(__s->b))==0) return;
                int c;
                
struct s_q31 sq31;
sq31.__s = __s;
sq31.c = &c;
sq31.a = &a;

                q31(&sq31);
            }

void q31( struct s_q31* __s ){

                    int d;
                    
struct s_s35 ss35;
ss35.__s = __s;
ss35.d = &d;

                    s35(&ss35);
                }

void s35( struct s_s35* __s ){

                        p23(__s->__s->__s);								//calls p at which is defined outside s.
                    }

