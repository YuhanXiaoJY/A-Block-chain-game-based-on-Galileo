/*
This file contains the shellcmd for the block chain game.
*/
#include<xinu>
#include<stdio.h>
using namespace std;


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
