/*
Expected output:
0 0 0 0 0 0 
0 1 0 0 0 0 
0 0 2 0 0 0 
0 0 0 0 0 0 
0 0 0 0 4 0 
0 0 0 0 0 0 

 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 

 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 

*/


#include<stdio.h>

int main()
{
		  int a[5] = {0,1,2,0,4};
		  int i,j,k,l;
f1:{
			  int b[3][6][6];
				int p;

			print:{
				for(j=0;j<3;j++)
				{
					for(k=0;k<6;k++)
					{
						for(l=0;l<6;l++)
						{
							if(p == 1)
							printf("%d ",b[j][k][l]);
							else
							b[j][k][l] = 0;
						}
						printf("\n");
					}
				
					printf("\n \n");
				}
			}
				
				//Initialize
				p = 0;
				print();
			

			  for(i=0;i<5;i++)
			  {
						 b[0][a[i]][a[i]] = a[i];
			  }
				
			p = 1;	
				print();

	}


	f1();

}

