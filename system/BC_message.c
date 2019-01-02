#include <xinu.h>
void BC_message(char* str, int initiator, int receiver, int mode, double amount){
	char initiator_dot[20];
	char receiver_dot[20];
	char s_amount[20];
	ftoa(amount, s_amount, 4);
	ip2dot(initiator, initiator_dot);
	ip2dot(receiver, receiver_dot);
	sprintf(str, "%s_%s_%d_%d", initiator_dot, receiver_dot, mode, (int)(amount));
}

bool8 BC_decode(char* buff, int len, int* initiator, int* receiver, int* protocol, double* amount){
	char str[4][20];
	
	int count = 0, i = 0, k = 0;
	for (k = 0; k < 4; k++){
		for (i = 0; buff[count] != '_' && buff[count] != 0; i++, count++){
			str[k][i] = buff[count];
		}
		str[k][i] = 0;
		count++;
	}

	//printf("BC_decode:initiator:%s\nreceiver:%s\nprotocal:%s\namount:%s\n", str[0], str[1], str[2], str[3]);
	//printf("len(str[0]): %d\n", strlen(str[0]));	
	//printf("len(str[1]): %d\n", strlen(str[1]));	
	//printf("len(str[2]): %d\n", strlen(str[2]));	
	//printf("len(str[3]): %d\n", strlen(str[3]));	
	dot2ip(str[0], (uint32 *)initiator);
	dot2ip(str[1], (uint32 *)receiver);
	*protocol = atoi(str[2]);
	*amount = atof(str[3]);
	return TRUE;
}
