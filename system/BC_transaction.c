#include <xinu.h>

bool8 BC_transaction(int id, double amount){
	if (id < 0 || id > bcdevnum){
		printf("Wrong device ID!\n");
		return FALSE;
	}

	if (bcdevice[id].ip == bcid.ip){
		printf("Can't not initialize a transaction with yourself!\n");
		return FALSE;
	}

	char s[100];
	BC_message(s, bcid.ip, bcdevice[id].ip, 1, amount);
	
	int retval = udp_sendto(bcid.slot, bcdevice[id].ip, BCPORT, s, strlen(s));
	if (retval == SYSERR)
		return FALSE;
	return TRUE;
}

