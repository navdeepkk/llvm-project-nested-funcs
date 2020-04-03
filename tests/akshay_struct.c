#include<stdio.h>

struct s{
	int a;
};



int main(){
	
	struct s{
		int a;
	};

	foo:{
		
		struct s{
			int a;
		};
		
		bar1:{
			struct s{
				int a;
			};
		}

		bar2:{
			struct s s1;
		}
	}
return 0;
}
