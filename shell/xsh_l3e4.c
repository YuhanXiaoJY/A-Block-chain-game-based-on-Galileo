/* xsh_l3e4.c - wakeup calls wait */

#include <xinu.h>
#include <stdio.h>

uint32 callwait;
sid32 s_wait;
void work(void);
void Proc(int i);
/*------------------------------------------------------------------------
 * xsh_l3e4.c - wakeup calls wait
 *------------------------------------------------------------------------
 */
shellcmd xsh_l3e4(int nargs, char *args[])
{
	callwait = 1;
	work();
	
        return 0;
}

void Proc(int i)
{
	kprintf("Proc %u ", currpid);
	kprintf("is going to sleep.\n");
	sleep(1);
	kprintf("Proc %u has been wakend.\n",currpid);
}

void work(void)
{
	s_wait = semcreate(3);
	int i;
	char *a[5] = {"Proc1", "Proc2", "Proc3", "Proc4","Proc5"};
	pid32 p;
	for(i=0;i<=4;i++)
	{
		p = create(&Proc, 1024, 10+i, a[i], 0);
		resume(p);
		kprintf("Proc %u has been created.\n", p);
	}
}
