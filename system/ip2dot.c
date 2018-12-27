/*
This file converts ip of the 'int' type to chars.
*/
#include<xinu.h>
#include<stdio.h>

void ip2dot(int ip, char* s)
{
	sprintf(s, "%d.%d.%d.%d", (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff
								(ip)&0xff);
}
