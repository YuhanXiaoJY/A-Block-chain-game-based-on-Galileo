#include <xinu.h>
#include <stdio.h>

void BC_log()
{
	char tmp[50];
	int ip = bcid.ip;
	sprintf(tmp, "%d.%d.%d.%d", (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff
								,(ip)&0xff);
	kprintf("Log info:\n");
	kprintf("--------------------------------\n");
	kprintf("My ip: %s\n", tmp);
	kprintf("My balance: %f\n", bcid.amount);
	kprintf("My miningIncome: %f\n", bcid.miningIncome);
	


}
