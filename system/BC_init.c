#include<xinu.h>
#include<stdio.h>

void BC_init()
{
	bcid.amount = 100.0;
	bcid.miningIncome = 0.0;
	bcid.ip = getlocalip();
	bcid.slot = udp_register(0, BCPORT, BCPORT);
	bcdevnum = 0;
	nbclog = 0;
	nbc_ilog = 0;
	nbc_rlog = 0;
	nbc_mlog = 0;
}
