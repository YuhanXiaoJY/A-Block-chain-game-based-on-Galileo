#include<xinu.h>
#include<stdio.h>

void BC_init()
{
	bcid.amount = 100.0;
	bcid.miningIncome = 0.0;
	bcid.ip = getlocalip();
}
