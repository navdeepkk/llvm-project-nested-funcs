#include<stdio.h>

void main(){
    int a;
    r:{
        int b = 5;
            p:{
								static int b = 5;
                b--;
                printf("%d \n", b);
                if(b==0) return;
                int c;
                q:{
                    int d;
                    s:{
                        p();
                    }
                    s();
                }
                q();
            }
        p();    
    }
    r();
    return;
}

