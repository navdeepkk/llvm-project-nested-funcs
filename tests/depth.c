//intended output
//4 3 2 1 0


#include<stdio.h>

void main(){
    r:{
        int b = 5;
            p:{
								int a = 0;
                b--;
                printf("b:%d a:%d\n",a ,b);
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
}

