#include <xinu.h>
#include <stdio.h>

static void transaction(){	
	int receiver;
	double amount;

	printf("Enter ID and amount to start a transaction: ");
	scanf("%d", (int)(&receiver));
	scanf("%f", (int)(&amount));
	if (BC_transaction(receiver, amount) == FALSE){
		printf("Error in initializing transaction!\n");
	}else{
		printf("Succeed in initializing transaction!\n");
	}
}

void BC_cmd(){
	transaction();
	return;

	int func;

	printf("FUNCTION:\t1.TRANSACTION\t2.LOG\nEnter a number:");
	scanf("%d", (int)(&func));
	
	switch(func){
		case 1: transaction(); break;
		case 2: BC_log(); break;
		default: printf("Please enter a valid number!\n");
	}
	
	return;
}

