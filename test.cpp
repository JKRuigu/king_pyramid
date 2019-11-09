bool validatePop(int l,int arr[]){
	int sum = getSum(l,arr);
	if(sum >0)
		return true;
	else
		return false;
}

bool validatePush(int l,int arr[],int num){
	int s=getSmallest(l,arr);
	bool isTrue = false;

	if(s <l)
		
}

int selectSlot(char a,char b,int l,int arr,int arr2[],int arr3[],int num){
	if(a == 'A' || a == 'a'){
		if(b == 1){
			bool isTrue = validatePop(l,arr);
			if(isTrue == 0)
				return 1;	
			else
				return 0;
		}else{
			bool isTrue = validatePush(l,arr,num);	
			if(isTrue == 0)
				return 1;	
			else
				return 0;	
		}
			
	}else if(a == 'B' || a == 'b'){
		return 2;	
	}else if(a == 'C' || a == 'c'){
		return 3;	
	}else{
		return 0;	
	}
}

