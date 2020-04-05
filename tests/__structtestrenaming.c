struct s_manipulatePoints19 {
};

struct s_setPoints31 {
struct s_manipulatePoints19 *__s;
int * i;
struct pair23 * pairs;
};

struct s_finddistance43 {
struct s_manipulatePoints19 *__s;
int * i;
struct pair23 * pairs;
};

struct point{

		int x, y;
		
struct loc{

			int x,y;	
		};
	};

struct pair23{

			struct point p1, p2;
		};

void manipulatePoints19( struct s_manipulatePoints19*);
void setPoints31( struct s_setPoints31*);
void finddistance43( struct s_finddistance43*);


#include<math.h>
#include<stdio.h>



	

int main(){
	
	
struct s_manipulatePoints19 smanipulatePoints19;

	manipulatePoints19(&smanipulatePoints19);
	return 0;
}


void manipulatePoints19( struct s_manipulatePoints19* __s ){

		


struct pair23 pairs[5];
		int i;

		
struct s_setPoints31 ssetPoints31;
ssetPoints31.__s = __s;
ssetPoints31.i = &i;
ssetPoints31.pairs = &pairs;

		setPoints31(&ssetPoints31);
			
		
struct s_finddistance43 sfinddistance43;
sfinddistance43.__s = __s;
sfinddistance43.i = &i;
sfinddistance43.pairs = &pairs;

		finddistance43(&sfinddistance43);	
	}

void setPoints31( struct s_setPoints31* __s ){

			for((*(__s->i)) = 0; (*(__s->i)) < 5; (*(__s->i)) ++){
				(__s->pairs)[(*(__s->i))].p1.x = (*(__s->i));
				(__s->pairs)[(*(__s->i))].p1.y = (*(__s->i));
				(__s->pairs)[(*(__s->i))].p2.x = (*(__s->i));
				(__s->pairs)[(*(__s->i))].p2.y = (*(__s->i));
			}					
		}

void finddistance43( struct s_finddistance43* __s ){

			for((*(__s->i)) = 0; (*(__s->i)) < 5; (*(__s->i)) ++){
				printf("distance is: %f\n", sqrt(pow((__s->pairs)[(*(__s->i))].p2.x - (__s->pairs)[(*(__s->i))].p1.x, 2) - pow((__s->pairs)[(*(__s->i))].p2.x - (__s->pairs)[(*(__s->i))].p1.x, 2)) );
			}	
		}

