#include<stdio.h>

int main(){
r:{
        int b;
            p:{
                b--;
                printf("%d \n", b);
                if(b==0) return 0;
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
}
