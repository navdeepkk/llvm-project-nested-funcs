struct s_foo11 {
};

struct s_foe28 {
struct s_foo11 *__s;
int * x;
};

struct s_bar15 {
struct s_foo11 *__s;
int * x;
};

struct s_label18 {
struct s_bar15 *__s;
};

void foo11( struct s_foo11*);
void bar15( struct s_bar15*);
void foe28( struct s_foe28*);
void label18( struct s_label18*);


#include<stdio.h>

void foo(){
	int x;
}

int main(){
	foo();

	
struct s_foo11 sfoo11;


	foo11(&sfoo11);

}


void foo11( struct s_foo11* __s ){

		int x;
		
struct s_bar15 sbar15;
sbar15.__s = __s;
sbar15.x = &x;

		if(1){
			bar15(&sbar15);
		}
		bar15(&sbar15);
		
struct s_foe28 sfoe28;
sfoe28.__s = __s;
sfoe28.x = &x;

		foo11(__s);
		int a;		
	}

void bar15( struct s_bar15* __s ){

			
struct s_label18 slabel18;
slabel18.__s = __s;
	
		}

void foe28( struct s_foe28* __s ){

			struct s_bar15 sbar1530;
sbar1530.__s = __s->__s;
sbar1530.x = __s->x;
bar15(&sbar1530);
		}

void label18( struct s_label18* __s ){

				foo11(__s->__s->__s);
			}

