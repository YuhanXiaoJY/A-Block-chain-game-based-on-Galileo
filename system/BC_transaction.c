#include <xinu.h>

bool8 BC_transaction(int id, double amount){
	int ip;
	if (id < 0 || id > bcdevnum){
		printf("Wrong device ID!\n");
		return False;
	}

	if (bcdevice[id].ip == bcid.ip){
		printf("Can't not initialize a transaction with yourself!\n");
		return False;
	}

	char s[100];
	BC_message(s, bcid.ip, ip, 1, amount);
	udp_sendto(bcid.slot, ip, BCPORT, s, strlen(s));
	
	return True;
}

