/* xsh_l4e1 two kinds of I/O.c - xshexit */

#include <xinu.h>

/*------------------------------------------------------------------------
 * xsh_l4e1
 *------------------------------------------------------------------------
 */
char buffer[1200];
void Proc_read(pid32 pid);
shellcmd xsh_l4e1(int nargs, char *args[])
{
	pid32 mainpid;
	mainpid = getpid();
	struct procent * prptr;
	prptr = &proctab[mainpid];
	
	resume(create(Proc_read, 1024, 10, "Proc_read", 1, mainpid));
	umsg32 msg ;
	while((msg = recvclr()) == OK)
	{
		kprintf("sleeping.\n");
		sleep(1);
	}

	//kprintf("%s\n",msg);
	kprintf("buffer: %s\n", buffer);
	return 0;
}

void Proc_read(pid32 pid)
{
	kprintf("Proc_read is running.\n");
	int retval;
	retval = read(CONSOLE, buffer, 10);
	kprintf("retval %d\n",retval);
	kprintf("read done!\n");
	buffer[retval-1] = '\0';
	umsg32 msg = "readok";
	send(pid, msg);
	
}
