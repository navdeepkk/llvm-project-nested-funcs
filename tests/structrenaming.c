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

	struct struct2{
		int r;
	};

	struct struct2 struct2_var; // refers to struct2 in cases
	struct2_var.r = 8;

	f1:{
	   /*This represents that structure variable with same type in same function resolves to two different 
	     declarations based on scope. 
	     jay and viru both are of type struct1, but jay resolves to global struct1 
	     and viru resolves to struct1 inside f1.			
	    */
	   struct struct1 jay;  
	   struct struct1{
		   struct struct2 x;             // x shall resolve to struct2 in cases(). (Expected output 4)
		   int y;
	   };
	   struct struct1 viru;

	   jay.b[2] = 4;
	   viru.x.r = 5; 		// This line will throw compiler error, if structures are not resolved properly.

	f2:{
		   struct node{
			   struct node* node;  // struct member refering to same struct shall also get renamed. (Expected Output 4)
			   int data;
		   };
	
		   struct node ll;
		   ll.data = 8;
	   }

	f3:{
		struct node{
			struct node* node;
			int my_data;
			};
		
		struct node ll; // this shall resolve to node declaration in case/f1/f3
		ll.my_data = 4; // otherwise this will throw compiler error.
	}
   }
}

int main()
{
	cases();
	return 0;
}
