int  a;

int main(){
	int b;
	foo:{
			a = a + 1;
			b = b + 1; 
		}
	foo();
	return 0;
}
