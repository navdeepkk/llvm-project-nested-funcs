#include<stdio.h>


int main()
{

	int a[5];
	int b = 0;

	foo:{
		a[0] = 7;

		if(b==1) // i.e. if called by fun
		{
			a[2] = 9;
		}
		
		fun:{
			int a[3];
			
			a[2] = 3;
			b = 1;
			foo();
			
  		     }
		
		if(b==0) //i.e. if called by main
		{
			fun();
		}

	     }
	foo();
/*verification*/
	printf("a[5] = ");
	for(int i = 0;i<5;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	
	return 0;
}


// expected output : 
// a[5] = 7 0 9 0 0
// a[3] = 0 0 3
// or garbage values in place of 0
