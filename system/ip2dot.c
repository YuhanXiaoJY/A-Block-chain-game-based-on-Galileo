/*
This file converts ip of the 'int' type to chars.
*/
#include<xinu.h>
#include<stdio.h>

char * ip2dot(int ip)
{
	char * a[21];
	sprintf(a, "%d.%d.%d.%d", (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff
								(ip)&0xff));
	return a
}
