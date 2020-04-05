#include<math.h>
#include<stdio.h>


struct point{
		int x, y;
		struct loc{
			int x,y;	
		};
	};	

int main(){
	
	manipulatePoints:{
		struct pair{
			struct point p1, p2;
		}pairs[5];
		int i;

		setPoints:{
			for(i = 0; i < 5; i ++){
				pairs[i].p1.x = i;
				pairs[i].p1.y = i;
				pairs[i].p2.x = i;
				pairs[i].p2.y = i;
			}					
		}
		setPoints();
			
		finddistance:{
			for(i = 0; i < 5; i ++){
				printf("distance is: %f\n", sqrt(pow(pairs[i].p2.x - pairs[i].p1.x, 2) - pow(pairs[i].p2.x - pairs[i].p1.x, 2)) );
			}	
		}
		finddistance();	
	}
	manipulatePoints();
	return 0;
}
