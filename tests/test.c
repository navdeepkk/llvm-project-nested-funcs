//#include<stdio.h>

/*
struct point{
			int x, y;
		};

int main(){
	foo:{
	struct point{
			int x, y;
		};
		bar:{
			struct point p1;
			p1.x = 1;
			p1.y = 1;
			printf("%d %d\n", p1.x, p1.y);
		}
	bar();
	}
	foo();
	return 0;
}
*/

/*
int y = 5;
int main(){
	label:{
			static int x = 5;
		foo:{
			int z = 5;
			printf("%d\n",x);
			printf("%d\n",y);
			printf("%d\n",z);
		}
		foo();
	}
	label();
	return 0;
}
*/

	struct point{
		int x,y;
	};
int main(){
	struct point{
		int x,y;
	};

		struct point p1;
	label:{
	}

return 0;
}
















