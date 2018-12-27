/* xsh_l4e2 CONSOLE - xshexit */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_l4e2
 *------------------------------------------------------------------------
 */

shellcmd xsh_l4e2(int nargs, char *args[])
{
	int retval1, retval2;
	char buffer[100];
	retval1 = read(CONSOLE, buffer, 100);
	//kprintf("retval1: %d\n", retval1);
	buffer[retval1-1] = '\0';	//buffer[retval1] is a newline descriptor
	//kprintf("%s\n", buffer);
	
	if(strcmp(buffer, "CONSOLE")==0)
	{
		retval2 = open(CONSOLE, NULL, NULL);
		kprintf("Device %s has been opened.\n",buffer);
		kprintf("the return value of open:%d\n",retval2);
	}
	else
	{
		kprintf("Bad device name.\n");
	}
	//int i;
	//for(i=1;i<=10;i++)
		//kprintf("%d\n", i);

	
	return 0;
}
