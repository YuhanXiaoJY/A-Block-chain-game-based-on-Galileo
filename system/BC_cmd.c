#include <xinu.h>
#include <stdio.h>

static void transaction(){	
	int receiver;
	double amount;
	char s_amount[20];
	char s_receiver[20];

	printf("Enter ID and amount to start a transaction:\n");
	printf("ID:");
	read(CONSOLE, s_receiver, 15);
	printf("AMOUNT:");
	read(CONSOLE, s_amount, 15);
	
	receiver = atoi(s_receiver);
	amount = atof(s_amount);
	ftoa(amount, s_amount, 2);
	
	// DEBUG
	//printf("ID: %d\n", receiver);
	//printf("AMOUNT: %s\n", s_amount);
	
	
	
	if (BC_transaction(receiver, amount) == FALSE){
		printf("Error in initializing transaction!\n");
	}else{
		printf("Succeed in initializing transaction!\n");
	}
}

void BC_cmd(){
	//transaction();
	//return;

	int func;
	char s_func[20];

	printf("FUNCTION:\n0.SCAN\n1.TRANSACTION\n2.LOG\n3.ILOG\n4.RLOG\n5.MLOG\nEnter a number:");
	read(CONSOLE, s_func, 15);
	func = atoi(s_func);
	
	switch(func){
		case 0: BC_scan();	break;
		case 1: transaction(); break;
		case 2: BC_logging(); break;
		case 3: BC_ilogging(); break;
		case 4: BC_rlogging(); break;
		case 5: BC_mlogging(); break;
		default: printf("Please enter a valid number!\n");
	}
	
	return;
}

