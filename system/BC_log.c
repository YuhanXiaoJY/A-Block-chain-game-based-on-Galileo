#include <xinu.h>
#include <stdio.h>

void BC_logging()
{
	char tmp[50];
	int ip = bcid.ip;
	ip2dot(ip, tmp);

	kprintf("Log info:\n");
	kprintf("--------------------------------\n");
	kprintf("My ip: %s\n", tmp);
	kprintf("Initial amount: 100\n");
	kprintf("My balance: %f\n", bcid.amount);
	kprintf("My miningIncome: %f\n\n", bcid.miningIncome);
	int i;
	for (i = 0; i < nbclog; i++)
	{
		kprintf("Log list:\n");
		char ip1[50];
		char ip2[50];
		char myip[50];
		int tmp1 = bclog[i].initiator;
		int tmp2 = bclog[i].receiver;
		int tmp3 = bcid.ip;
		ip2dot(tmp1, ip1);
		ip2dot(tmp2, ip2);
		ip2dot(tmp3, myip);
		kprintf("[log]%-3d: %s -> %s  %f %d\n", i, ip1, ip2, bclog[i].transaction, bclog[i].finished);
	}
	kprintf("-----%d logs in all------\n\n", nbclog);
}

void BC_ilogging()
{
	int i;
	double send = 0.0;
	kprintf("Initiating list:\n");
	kprintf("-----------------\n");
	for(i = 0; i < nbc_ilog; i++)
	{
		char ip1[50];
		char ip2[50];
		char myip[50];
		int tmp1 = bc_ilog[i].initiator;
		int tmp2 = bc_ilog[i].receiver;
		int tmp3 = bcid.ip;
		ip2dot(tmp1, ip1);
		ip2dot(tmp2, ip2);
		ip2dot(tmp3, myip);
		if(tmp1 != tmp3)
		{
			kprintf("BC_ilogging error: initiator %s expected but get %s.\n", myip, ip1);
			continue;
		}

		kprintf("[log]%-3d: send %f to %s.\n", i, bc_ilog[i].transaction, ip2);
		send += bc_ilog[i].transaction;
	}
	kprintf("-----send %f in all------\n\n", send);
}

void BC_rlogging()
{
	int i;
	double income = 0.0;
	kprintf("Receiving list:\n");
	kprintf("-----------------\n");
	for(i = 0; i < nbc_rlog; i++)
	{
		char ip1[50];
		char ip2[50];
		char myip[50];
		int tmp1 = bc_rlog[i].initiator;
		int tmp2 = bc_rlog[i].receiver;
		int tmp3 = bcid.ip;
		ip2dot(tmp1, ip1);
		ip2dot(tmp2, ip2);
		ip2dot(tmp3, myip);
		if(tmp2 != tmp3)
		{
			kprintf("BC_rlogging error: receiver %s expected but get %s.\n", myip, ip2);
			continue;
		}

		kprintf("[log]%-3d: receive %f from %s.\n", i, bc_rlog[i].transaction, ip1);
		income += bc_rlog[i].transaction;
	}
	kprintf("-----receive %f in all------\n\n", income);
}

void BC_mlogging()
{
	int i;
	double income = 0.0;
	kprintf("Mining list:\n");
	kprintf("-----------------\n");
	for(i = 0; i < nbc_mlog; i++)
	{
		char ip1[50];
		char ip2[50];
		char myip[50];
		int tmp1 = bc_mlog[i].initiator;
		int tmp2 = bc_mlog[i].receiver;
		int tmp3 = bcid.ip;
		ip2dot(tmp1, ip1);
		ip2dot(tmp2, ip2);
		ip2dot(tmp3, myip);
		
		kprintf("[log]%-3d: mine for (%s, %s, %f) and get %f.\n", 
			i, ip1, ip2, bc_mlog[i].transaction, bc_mlog[i].fee);
		income += bc_mlog[i].fee;
	}
	kprintf("-----get %f in all as a miner------\n\n", income);
}
