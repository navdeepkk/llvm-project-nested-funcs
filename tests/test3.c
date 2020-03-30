#include<stdio.h>

int main(){
	foo:{
		p:{
			int i;
		}
	int i;
	q:{
		r:{
				s:{
					p();
				}
				p();
				s();
			}
		p();
		r();
		}
q();
}
	return 0;
}
