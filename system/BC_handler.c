#include <xinu.h>
#define EPS 1e-2

static bool8 equals(double a, double b){
	double x = a - b;
	return x < EPS && x > -EPS;
}

// get protocal1, behave as a receiver, broadcast protocal2 to find a miner.
static bool8 protocol1(int ip1, int ip2, double amount ){
	int i;
	if(bcdevnum <= 0){
		kprintf("[protocal1]:no active device, where did you get the protocal1?\n");
		return FALSE;
	}
	if(ip2 != bcid.ip)
	{
		kprintf("[protocal1]:receiver ip is wrong!\n");
		return FALSE;
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
		kprintf("[protocal1]send to %s successfully.\n",tmp);
	}
	return TRUE;
	
}

// get protocal2, behave as miner candidate, send protocal3 to the receiver
static bool8 protocol2(int ip1, int ip2, double amount){

	// create a bc_mlog
	bc_mlog[nbc_mlog].initiator = ip1;
	bc_mlog[nbc_mlog].receiver = ip2;
	bc_mlog[nbc_mlog].transaction = amount;
	bc_mlog[nbc_mlog].fee = 0.0;
	bc_mlog[nbc_mlog].isok = FALSE;
	bc_mlog[nbc_mlog].progress = 1;
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
	kprintf("[protocal2]:send to %s successfully.\n",tmp);
	return TRUE;
}

//get protocal3, behave as a receiver, send the protocal4 to the selected miner
static bool8 protocol3(int ip1, int ip2, double amount, uint32 minerip){
	if(ip2 != bcid.ip)
	{
		kprintf("[protocal3]:receiver ip is wrong\n");
		return FALSE;
	}
	
	int i;
	bool8 flag = FALSE;
	for(i = 0; i < nbc_rlog; i++)
	{
		struct BC_rlog tmp_log = bc_rlog[i];
		if(ip1 == tmp_log.initiator && ip2 == tmp_log.receiver
			&& equals(amount, tmp_log.transaction) && tmp_log.waiting == TRUE)
		{
			flag = TRUE;
			bc_rlog[i].waiting = FALSE;
			bc_rlog[i].miner = minerip;
			bc_rlog[i].isok = TRUE;
			bcid.amount += 0.9*amount;
			char s[100];
			char tmp[50];
			ip2dot(minerip, tmp);
			BC_message(s, ip1, ip2, 4, amount);
	
			int retval = udp_sendto(bcid.slot, minerip, BCPORT, s, strlen(s));
			if (retval == SYSERR)
			{
				kprintf("[protocal3]:fail to send message to %s\n",tmp);
				return FALSE;
			}
			kprintf("[protocal3]:send to %s successfully.\n",tmp);
			break;
		}
		// else if(ip1 == tmp_log.initiator && ip2 == tmp_log.receiver
		// 	&& equals(amount, tmp_log.transaction) && tmp_log.waiting == FALSE)
		// {
		// 	return FALSE;
		// }
	}
	if(flag == FALSE)
	{
		kprintf("[protocal3]:cannot find the transaction.\n");
		return FALSE;
	}

	for(i = 0; i < bcdevnum; i++)
	{
		int ip3 = bcdevice[i].ip;
		char s[100];
		char tmp[50];
		ip2dot(ip3, tmp);
		BC_message(s, ip1, ip2, 6, amount);
	
		int retval = udp_sendto(bcid.slot, ip3, BCPORT, s, strlen(s));
		if (retval == SYSERR)
		{
			kprintf("[protocal3]:fail to send message to %s\n",tmp);
			continue;
		}
		kprintf("[protocal3]send to %s successfully.\n",tmp);
	}
	return TRUE;
	
}

//get protocal4, behave as a miner, send protocal to initiator and broadcast
static bool8 protocol4(int ip1, int ip2, double amount){
	int i;
	bool8 flag = FALSE;
	for(i = nbc_mlog - 1; i >= 0; i--)
	{
		struct BC_mlog tmp_log = bc_mlog[i];
		if(ip1 == tmp_log.initiator && ip2 == tmp_log.receiver
			&& equals(amount, tmp_log.transaction) && tmp_log.progress == 1)
		{// match the specified transaction
			// find, finish the mlog info
			bc_mlog[i].progress = 2;
			bc_mlog[i].fee = amount/10;
			kprintf("[**************]:amount: %f\n", amount);
			kprintf("[**************]:fee: %f\n", 0.1*amount);
			bc_mlog[i].isok = TRUE;
			bcid.amount += 0.1 * amount;
			bcid.miningIncome += 0.1 * amount;
			char s[100];
			char tmp[50];
			ip2dot(ip1, tmp);
			BC_message(s, ip1, ip2, 5, amount);
	
			int retval = udp_sendto(bcid.slot, ip1, BCPORT, s, strlen(s));
			if (retval == SYSERR)
			{
				kprintf("[protocal4]:fail to send message to %s\n",tmp);
				return FALSE;
			}
			kprintf("[protocal4]:send to %s successfully.\n",tmp);
			flag = TRUE;
			break;
		}
	
	}
	if(flag == FALSE)
	{// cannot find the transaction
		kprintf("[protocal4]:cannot find the transaction.\n");
		return FALSE;
	}
	//broadcast
	for(i = 0; i < bcdevnum; i++)
	{
		uint32 ip3 = bcdevice[i].ip;
		char s[100];
		char tmp[50];
		ip2dot(ip3, tmp);
		BC_message(s, ip1, ip2, 6, amount);
	
		int retval = udp_sendto(bcid.slot, ip3, BCPORT, s, strlen(s));
		if (retval == SYSERR)
		{
			kprintf("[protocal4]:fail to broadcast to %s\n",tmp);
			continue;
		}
	}
	kprintf("[protocal4]:broadcast done!\n");
	return TRUE;
}

// get protocol5, behave as a initiator
// transaction is successful and then minus my account, keep a record
static bool8 protocol5(int ip1, int ip2, double amount){
	if (ip1 != bcid.ip){
		kprintf("[protocol5]: initiator ip is wrong.\n");
		return FALSE;
	}
	char sip1[20];
	char sip2[20];
	ip2dot(ip1, sip1);
	ip2dot(ip2, sip2);
	// kprintf("ip2: %s\n", sip2);
	// kprintf("amount: %f\n", amount);
	int i;
	for (i = 0; i < nbc_ilog; i++){
		ip2dot(bc_ilog[i].initiator, sip1);
		ip2dot(bc_ilog[i].receiver, sip2);

		// kprintf("%s->%s: %f\n", sip1, sip2, bc_ilog[i].transaction);
		if (bc_ilog[i].receiver == ip2 && equals(bc_ilog[i].transaction, amount))
			break;
	}
	if (i == nbc_ilog){
		// did not find ilog record
		kprintf("[protocol5]: fail to find related record.\n");
		return FALSE;
	}

	// found ilog which is bc_ilog[i] and finish this transaction
	bc_ilog[i].isok = TRUE;
	bcid.amount -= amount;
	kprintf("[protocal5]: transaction done!\n");
	return TRUE;
}


// get protocol6, behave as an outsider
// keep bc_log
static void protocol6(int ip1, int ip2, double amount){
	int i = 0;
	struct BClog plog;

	for (i = 0; i < nbclog; i++){
		plog = bclog[i];
		if (plog.initiator == ip1 && plog.receiver == ip2 && equals(plog.transaction, amount) && plog.finished == FALSE)
			break;
	}
	
	if (i == nbclog){
		// did not find an bclog, then create one
		bclog[i].initiator = ip1;
		bclog[i].receiver = ip2;
		bclog[i].transaction = amount;
		bclog[i].finished = FALSE;
		nbclog ++;
		kprintf("[protocol6]:create log.\n");
	}else{
		// found an bclog
		bclog[i].finished = TRUE;
		kprintf("[protocal6]:valid log %d\n", nbclog - 1);
	}
	
}



void BC_handler(){
	char buff[105];
	uint32 remip;
	uint16 remport;

	int initiator;
	int reciver;
	int protocol;
	double amount;

	while(1){

		sleepms(100);
		//kprintf("[BC_handler]:ready to receive protocol.\n");
		int retval = udp_recvaddr(bcid.slot, &remip, &remport, buff, 100, 100);
		//kprintf("[BC_handler]:receive protocol successfully.\n");
		if (retval == SYSERR || retval == TIMEOUT)
			continue;
		BC_decode(buff, retval, &initiator, &reciver, &protocol, &amount);
		kprintf("udp packet: %s\n", buff);
		
		wait(lock);
		switch(protocol){
			case 1:	protocol1(initiator, reciver, amount); break;
			case 2: protocol2(initiator, reciver, amount); break;
			case 3: protocol3(initiator, reciver, amount, remip); break;
			case 4: protocol4(initiator, reciver, amount); break;
			case 5: protocol5(initiator, reciver, amount); break;
			case 6: protocol6(initiator, reciver, amount); break;
			default: printf("Wrong protocol code!\n"); break;
		}

		signal(lock);
	}	
}
