#include <xinu.h>
#include <stdio.h>

void BC_logging()
{
	char tmp[50];
	ip = bcid.ip;
	ip2dot(ip, tmp)

	kprintf("Log info:\n");
	kprintf("--------------------------------\n");
	kprintf("My ip: %s\n", tmp);
	kprintf("Initial amount: 100\n");
	kprintf("My balance: %f\n", bcid.amount);
	kprintf("My miningIncome: %f\n", bcid.miningIncome);
	BC_scan();
	BC_ilogging();
	BC_rlogging();
	BC_mlogging();

}

void BC_ilogging()
{
	int i;
	double send = 0.0;
	kprintf("\nInitiating list:\n");
	kprintf("-----------------\n");
	for(i = 0; i < nbc_ilog; i++)
	{
		char ip1[50];
		char ip2[50];
		char myip[50];
		tmp1 = bc_ilog[i].initiator;
		tmp2 = bc_ilog[i].receiver;
		tmp3 = getlocalip();
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
	kprintf("-----send %f in all------\n", send);
}

void BC_rlogging()
{
	int i;
	double income = 0.0;
	kprintf("\nReceiving list:\n");
	kprintf("-----------------\n");
	for(i = 0; i < nbc_rlog; i++)
	{
		char ip1[50];
		char ip2[50];
		char myip[50];
		tmp1 = bc_rlog[i].initiator;
		tmp2 = bc_rlog[i].receiver;
		tmp3 = getlocalip();
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
	kprintf("-----receive %f in all------\n", income);
}

void BC_mlogging()
{
	int i;
	double income = 0.0;
	kprintf("\nMining list:\n");
	kprintf("-----------------\n");
	for(i = 0; i < nbc_mlog; i++)
	{
		char ip1[50];
		char ip2[50];
		char myip[50];
		tmp1 = bc_mlog[i].initiator;
		tmp2 = bc_mlog[i].receiver;
		tmp3 = getlocalip();
		ip2dot(tmp1, ip1);
		ip2dot(tmp2, ip2);
		ip2dot(tmp3, myip);
		
		kprintf("[log]%-3d: mine for (%s, %s) and get %f.\n", i, ip1, ip2, bc_mlog[i].transaction);
		income += bc_mlog[i].transaction;
	}
	kprintf("-----get %f in all as a miner------\n", income);
}