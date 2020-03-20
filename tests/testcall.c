void foo(){
	p:{
	}
	p();
}


int main(){
	p:{
		q:{
				r:{
					p();
						if(1){
							p();	
					}
			}
		}p();
	}
	p();
	return 0;
}
