#include <xinu.h>

static void protocol1(){
	
}

static void protocol2(){
	
}

static void protocol3(){
	
}

static void protocol4(){
	
}

static void protocol5(){
	
}

static void protocol6(){
	
}

void BC_handler(){
	char buff[105];

	int initiator;
	int reciver;
	int protocol;
	double amount;

	while(1){
		sleepms(100);
		int retval = udp_recv(bcid.slot, buff, 100, 100);
		if (retval == SYSERR || retval == TIMEOUT)
			continue;
		BC_decode(buff, retval, &initiator, &reciver, &protocol, &amount);
		
		switch(protocol){
			case 1:	protocol1(); break;
			case 2: protocol2(); break;
			case 3: protocol3(); break;
			case 4: protocol4(); break;
			case 5: protocol5(); break;
			case 6: protocol6(); break;
			default: printf("Wrong protocol code!\n"); break;
		}
	}	
}
