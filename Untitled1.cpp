#include <stdio.h>
int main(){
	int price,choice,total;
	float finalamount;
	float discount;
	total=0;
	printf("Enter the price of an item:");
	scanf("%d",&price);
	while(price>0){
		printf("\nIf you want to buy another item press(1 for yes)(0 for no)");
		scanf("%d",&choice);
		
		if(choice==1){
			printf("\nEnter the price of an item:");
			scanf("%d",&price);
			
		}
		else{
			break;
		}
		total=total+price;
		
		if(total>10000){
			discount=total/10;
			finalamount=total-discount;
			
			
		}
		else{
			finalamount=total;
		}
	}
	printf("\nThe final amount is:%2f",finalamount);
	printf("\nThe discount is:%f",discount);
	printf("\nThe total price is:%d",total);
	
	
	
	return 0;
	
}
