#include <iostream>
#include <fstream>

using namespace std;
//GLOBAL VARIABLES
/**	
	Intialize
	Dispaly
	select level	
	Select SLOT A
	Get smallest value
	Select SLOT B
	Get smallest value
	validate
		Discard
			Select SLOT A			
			Select SLOT B		
		Remove smallest value
		Add value
			Select SLOT A				
**/

//Functions
int setLevel();
void start(bool isActive,int l,int arr[],int arr2[],int arr3[],int max);
int calculateTotal(int l);
void intializeGame(int l,int arr[]);
void displaySlot(int l,int arr[]);
void displayAll(int l,int arr[],int arr2[],int arr3[]);
int getSmallest(int l,int arr[]);
int pushNumber(int l,int arr[],int num);
void popNumber(int l,int arr[]);
int selectSlot(char a,char b);
int getSum(int l,int arr[]);
int selectSlotA(char a,int l,int arr[],int arr2[],int arr3[]);
void selectSlotB(char a,char b,int l,int num,int arr[],int arr2[],int arr3[]);
int validatePop2(int l,int arr[]);
void move(int index,char b,int l,int num,int arr[],int arr2[],int arr3[]);
void popNumber2(char a,int l,int arr[],int arr2[],int arr3[]);
void play(int l,int arr[],int arr2[],int arr3[],int num); 


int main(){
	int SIZE = 10;
	int slot1[SIZE]={0,0,0,0,0,0,0,0,0,0};
	int slot2[SIZE]={0,0,0,0,0,0,0,0,0,0};
	int home[SIZE]={0,0,0,0,0,0,0,0,0,0};
	int level =0;
	bool isActive = true;
	int max =0;
	cout<<"Welcome to King's Pyramid!"<<endl;
	level = setLevel();
	max = calculateTotal(level);
	intializeGame(level,slot1);

	start(isActive,level,home,slot1,slot2,max);
		
}

void start(bool isActive,int l,int arr[],int arr2[],int arr3[],int max){
	while(isActive){
		play(l,arr,arr2,arr3,max);	
	}
	
}

int setLevel(){
	int l =0;
	cout<<"Choose level between 3 -10"<<endl;
	cin>>l;	
	if(l>2 && l<=10)
		return l;
	else
		return setLevel();
}

int calculateTotal(int l){
	int sum =0;
	while(l>0){
		sum+=l;
		l--;		
	}
	return sum;	
}

int checkWin(int l,int arr[],int max){
	int sum=0,i =0;
		
	for(i=0; i<l; i++)
		sum+=arr[i];
	if(sum == max)
		return 1;	
	else
		return 0;
}

void play(int l,int arr[],int arr2[],int arr3[],int max){
	int isWin = checkWin(l,arr,max);
	if(isWin == 1){
		if(l!=10){
			cout<<"Congratulations! You have completed level "<<l<<endl;
			cout<<"You have unlocked level "<<(l+1)<<endl;
			int level = setLevel();
			int max = calculateTotal(level);			
			int SIZE = 10;
			int slot1[SIZE]={0,0,0,0,0,0,0,0,0,0};
			int slot2[SIZE]={0,0,0,0,0,0,0,0,0,0};
			int home[SIZE]={0,0,0,0,0,0,0,0,0,0};			
			intializeGame(level,slot1);

			start(true,level,home,slot1,slot2,max);
	
		}else{
			cout<<"Congratulations You have completed All the levels"<<endl;
			cout<<"Thanks!";
		}
		
	}else{		
		char c,a;
		displayAll(l,arr,arr2,arr3);
		cout<<"Select(1) Home - A Slot1 - B Slot - C ";
		cin>>c;
		int num = selectSlotA(c,l,arr,arr2,arr3);
		
		if(num != 0){
			cout<<"Select(2) Home - A Slot1 - B Slot - C ";
			cin>>a;
			selectSlotB(a,c,l,num,arr,arr2,arr3);
		}
		cout<<"---------------------------------------------------------------"<<endl;
	}
}

void intializeGame(int l,int arr[]){
	ifstream dbFile("db.txt");
	int i;	
	for(i=0; i<l; i++)
		arr[i]=(i+1);			
}

void displaySlot(int l,int arr[]){
	int i;
	for(i=0; i<l; i++)
		cout<<arr[i]<<", ";
}

void displayAll(int l,int arr[],int arr2[],int arr3[]){
	cout<<"Home: ";
	displaySlot(l,arr);
	cout<<"Slot1: ";
	displaySlot(l,arr2);
	cout<<"Slot2: ";
	displaySlot(l,arr3);
	cout<<endl;	
}

int getSmallest(int l,int arr[]){
	int i,s=arr[0];	
	
	for(i=0; i<l; i++){
		if(s == 0)
			s=arr[i];
		if(arr[i] <s && arr[i] != 0)
			s = arr[i];
	}
			
	return s;
}

int pushNumber(int l,int arr[],int num){
	int i,s=getSmallest(l,arr),sum=getSum(l,arr);
	bool isTrue = false;

	if(num <s || sum ==0){
		for(i=0;i<l; i++){
			if(arr[i] == 0 && isTrue == 0){
				arr[i] = num;
				isTrue = true;		
			}
		}
		return 1;				
	}else{
		return 0;	
	}				
}

void popNumber(int l,int arr[]){
	int sum,i,s = getSmallest(l,arr);
	
	for(i=0;i<l; i++)
		if(arr[i] == s)
			arr[i] =0;
}

int getSum(int l,int arr[]){
	int i,sum =0;
	for(i=0;i<l; i++)
		sum+=arr[i];
	return sum;
}

int validatePop(int l,int arr[]){
	int sum = getSum(l,arr);

	if(sum >0)
		return 1;
	else
		return 0;
}

int validatePop2(int l,int arr[]){
	int isTrue = validatePop(l,arr);
	if(isTrue == 1){
		return getSmallest(l,arr);		
	}else{
		cout<<"Invalid move"<<endl;
		return 0;		
	} 
}

int selectSlotA(char a,int l,int arr[],int arr2[],int arr3[]){
	if(a == 'A' || a == 'a'){
		return validatePop2(l,arr);			
	}else if(a == 'B' || a == 'b'){
		return validatePop2(l,arr2);
	}else if(a == 'C' || a == 'c'){
		return validatePop2(l,arr3); 	
	}else{
		return 0;	
	}
}

void popNumber2(char a,int l,int arr[],int arr2[],int arr3[]){
	if(a == 'A' || a == 'a'){	
		popNumber(l,arr);			
	}else if(a == 'B' || a == 'b'){
		popNumber(l,arr2);
	}else{
		popNumber(l,arr3); 	
	}
}

void move(int index,char b,int l,int num,int arr[],int arr2[],int arr3[]){
	int result = 0;	

	if(index ==0){	
		result = pushNumber(l,arr,num);
	}else if(index == 1){
		result = pushNumber(l,arr2,num);
	}else{
		result = pushNumber(l,arr3,num);
	}

	if(result ==1){
		popNumber2(b,l,arr,arr2,arr3);
	}else{
		cout<<"Error!"<<endl;
	}
}


void selectSlotB(char a,char b,int l,int num,int arr[],int arr2[],int arr3[]){
	cout<<"From: "<<b<<" to "<<a<<endl;
	// cout<<"NUMBER IS"<<num<<endl;
	if(a == 'A' || a == 'a'){
		move(0,b,l,num,arr,arr2,arr3);			
	}else if(a == 'B' || a == 'b'){
		move(1,b,l,num,arr,arr2,arr3);
	}else if(a == 'C' || a == 'c'){
		move(2,b,l,num,arr,arr2,arr3);
	}
	
}





