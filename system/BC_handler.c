#include <xinu.h>

// get protocal1, behave as a receiver, broadcast protocal2 to find a miner.
static void protocol1(int ip1, int ip2, double amount ){
	int i;
	if(bcdevnum <= 0){
		kprintf("[protocal1]:no active device, where did you get the protocal1?\n");
		return FALSE;
	}
	if(ip2 != getlocalip())
	{
		kprintf("[protocal1]:receiver ip is wrong!\n");
		return FLASE;
	}
	//receiver create a BC_rlog
	bc_rlog[nbc_rlog].initiator = ip1;
	bc_rlog[nbc_rlog].receiver = ip2;
	bc_rlog[nbc_rlog].miner = -1;
	bc_rlog[nbc_rlog].transaction = amount;
	bc_rlog[nbc_rlog].isok = FALSE;
	bc_rlog[nbc_rlog].waiting = TRUE;
	nbc_rlog ++;


	for(i = 0; i < bcdevnum; i++)
	{
		int ip3 = bcdevice[i].ip;
		char s[100];
		char tmp[50];
		ip2dot(ip3, tmp);
		BC_message(s, ip1, ip2, 2, amount);
	
		int retval = udp_sendto(bcid.slot, ip3, BCPORT, s, strlen(s));
		if (retval == SYSERR)
		{
			kprintf("[protocal1]:fail to send message to %s\n",tmp);
			continue;
		}
	}
	
}

// get protocal2, behave as miner candidate, send protocal3 to the receiver
static void protocol2(int ip1, int ip2, double amount){

	// create a bc_mlog
	bc_mlog[nbc_mlog].initiator = ip1;
	bc_mlog[nbc_mlog].receiver = ip2;
	bc_mlog[nbc_mlog].transaction = amount;
	bc_mlog[nbc_mlog].isok = FALSE;
	bc_mlog[nbc_mlog].progress = 0;
	nbc_mlog ++;

	char s[100];
	char tmp[50];
	ip2dot(ip2, tmp);
	BC_message(s, ip1, ip2, 3, amount);
	
	int retval = udp_sendto(bcid.slot, ip2, BCPORT, s, strlen(s));
	if (retval == SYSERR)
	{
		kprintf("[protocal2]:fail to send message to %s\n",tmp);
		return FALSE;
	}
}

//get protocal3, behave as a receiver, send the protocal4 to the selected miner
static void protocol3(int ip1, int ip2, double amount, uint32 minerip){
	if(ip2 != getlocalip())
	{
		kprintf("[protocal3]:receiver ip is wrong\n");
		return FALSE;
	}
	int i;
	for(i = 0; i < nbc_rlog - 1; i++)
	{
		struct BC_rlog tmp_log = bc_rlog[i]
		if(ip1 == tmp_log.initiator && ip2 == tmp_log.receiver
			&& amount == tmp_log.transaction && tmp_log.waiting == TRUE)
		{
			bc_rlog[i].waiting = FALSE;
			bc_rlog[i].miner = minerip;
			char s[100];
			char tmp[50];
			ip2dot(miner, tmp);
			BC_message(s, ip1, ip2, 4, amount);
	
			int retval = udp_sendto(bcid.slot, minerip, BCPORT, s, strlen(s));
			if (retval == SYSERR)
			{
				kprintf("[protocal3]:fail to send message to %s\n",tmp);
				return FALSE;
			}
			return TRUE;
		}
		else if(ip1 == tmp_log.initiator && ip2 == tmp_log.receiver
			&& amount == tmp_log.transaction && tmp_log.waiting == FALSE)
		{
			return FALSE;
		}
	}
	kprintf("[protocal3]:cannot find the transaction.\n");
	return FALSE
}

static void protocol4(){
	
}

static void protocol5(){
	
}

static void protocol6(){
	
}

void BC_handler(){
	char buff[105];
	uint32 remip;
	uint32 remport;

	int initiator;
	int reciver;
	int protocol;
	double amount;

	while(1){
		sleepms(100);
		int retval = udp_recvaddr(bcid.slot, remip, remport, buff, 100, 100);
		if (retval == SYSERR || retval == TIMEOUT)
			continue;
		BC_decode(buff, retval, &initiator, &reciver, &protocol, &amount);
		
		switch(protocol){
			case 1:	protocol1(initiator, reciver, amount); break;
			case 2: protocol2(initiator, reciver, amount); break;
			case 3: protocol3(initiator, reciver, amount, remip); break;
			case 4: protocol4(); break;
			case 5: protocol5(); break;
			case 6: protocol6(); break;
			default: printf("Wrong protocol code!\n"); break;
		}
	}	
}
