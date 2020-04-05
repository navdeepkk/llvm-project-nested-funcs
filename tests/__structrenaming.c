struct s_f139 {
struct struct231 * struct2_var;
struct struct1 * i;
};

struct s_f373 {
struct s_f139 *__s;
struct struct1 * jay;
struct struct149 * viru;
};

struct s_f259 {
struct s_f139 *__s;
struct struct149 * viru;
struct struct1 * jay;
};

struct struct231{

		int r;
	};

struct struct149{

		   struct struct231 x;             // x shall resolve to struct2 in cases(). (Expected output 4)
		   int y;
	   };

struct node63{

			   struct node63* node;  // struct member refering to same struct shall also get renamed. (Expected Output 4)
			   int data;
		   };

struct node77{

			struct node77* node;
			int my_data;
			};

void f139( struct s_f139*);
void f259( struct s_f259*);
void f373( struct s_f373*);


/*
   This test case checks when structures are declared inside function/labels.

   Case 1: Structure declared in function and it's structure variable used in a nested function.
   Case 2: Structure declared in function has same name as structure in other function/ global structure. (Structure Renaming) 

   Expected output:
   1. Structure declarations are hoisted outside so as to enable access to nested functions.
   2. Structures are renamed to avoid compilation error when same name structures are declared in other nested functions.
   3. Structure variable declarations are resolved and rewritten to match corresponding structure.
   4. Structure variable declarations inside the structures are renamed.
 */

#include<stdio.h>


struct struct1{

	int a;
	int b[5];
};

//Case 1: Structure declared in function and it's structure variable used in a nested function.
//Case 2: Structure declared in function has same name as structure in other function/ global structure. (Structure Renaming) 
void cases()
{
	struct struct1 i; // refers to global structure

	


	struct struct231 struct2_var; // refers to struct2 in cases
	struct2_var.r = 8;

	
struct s_f139 sf139;
sf139.struct2_var = &struct2_var;
sf139.i = &i;

}

int main()
{
	cases();
	return 0;
}


void f139( struct s_f139* __s ){

	   /*This represents that structure variable with same type in same function resolves to two different 
	     declarations based on scope. 
	     jay and viru both are of type struct1, but jay resolves to global struct1 
	     and viru resolves to struct1 inside f1.			
	    */
	   struct struct1 jay;  
	   

	   struct struct149 viru;

	   jay.b[2] = 4;
	   viru.x.r = 5; 		// This line will throw compiler error, if structures are not resolved properly.

	
struct s_f259 sf259;
sf259.__s = __s;
sf259.viru = &viru;
sf259.jay = &jay;


	
struct s_f373 sf373;
sf373.__s = __s;
sf373.jay = &jay;
sf373.viru = &viru;

   }

void f259( struct s_f259* __s ){

		   

	
		   struct node63 ll;
		   ll.data = 8;
	   }

void f373( struct s_f373* __s ){

		

		
		struct node77 ll; // this shall resolve to node declaration in case/f1/f3
		ll.my_data = 4; // otherwise this will throw compiler error.
	}

