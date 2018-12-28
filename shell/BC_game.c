/*
This file contains the shellcmd for the block chain game.
*/
#include<xinu.h>
#include<stdio.h>

shellcmd xsh_BC()
{
	BC_init();
	resume(create(BC_handler, 8192, 100, "BC_handler", 0));
	while(1)
	{

		BC_cmd();
	}
	return 0;
}
