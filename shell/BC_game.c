/*
This file contains the shellcmd for the block chain game.
*/
#include<xinu.h>
#include<stdio.h>

shellcmd xsh_BC()
{
	BC_init();
	while(1)
	{
		BC_scan();
		BC_cmd();
	}
	return 0;
}
