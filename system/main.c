/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	char d[20] = "23.333";
	double num;
	num = atof(d);
	printf("*******num is %f\n", num);


	char* buff = "192.168.1.1_192.168.1.1_5_2.3333";
	int len = strlen(buff);
	int initiator, receiver, protocol;
	double amount;
	BC_decode(buff, len, &initiator, &receiver, &protocol, &amount);
	printf("main:\ninitiator:%d\nreceiver:%d\nprotocol:%d\namount:%f\n", initiator, receiver, protocol, amount);
	
	/* Run the Xinu shell */
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
