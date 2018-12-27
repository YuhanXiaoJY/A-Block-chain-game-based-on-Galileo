/* xsh_l3e2.c - trace clock */

#include <xinu.h>
#include <stdio.h>
void Proc1(void);
void Proc2(void);
uint32 Trace;
/*------------------------------------------------------------------------
 * xsh_l3e2.c - trace clock
 *------------------------------------------------------------------------
 */
shellcmd xsh_l3e2(int nargs, char *args[])
{
	Trace = 1;
	pid32 pid1, pid2;
	pid1 = create(&Proc1, 2048, 10, "Proc1",0);
	pid2 = create(&Proc2, 1024, 20, "Proc2",0);
	
	intmask mask1= disable();
	kprintf("Proc%u has been created.\n",pid1);
	resume(pid1);
	restore(mask1);

	mask1= disable();
	kprintf("Proc%u has been created.\n",pid2);
	resume(pid2);
	kprintf("myTrace is going to sleep.\n");
	restore(mask1);
	sleep(3);
	mask1 = disable();
	kprintf("myTrace finished.\n");
	restore(mask1);
	
        return 0;
}

void Proc1()
{
	intmask mask = disable();
	kprintf("Proc%u is running now.\n",currpid);
	restore(mask);
	int i;
	for(i=1;i<=3;i++)
	{
		sleep(1);
		mask = disable();
		kprintf("Proc%u has slept for %d seconds.\n", currpid,i);
		restore(mask);
	}
	mask = disable();
	kprintf("Proc%u finished.\n",currpid);
	restore(mask);
}

void Proc2()
{
	intmask mask = disable();
	kprintf("Proc%u is running now.\n",currpid);
	restore(mask);
	int i;
	for(i=1;i<=5;i++)
	{
		sleep(1);
		mask = disable();
		kprintf("Proc%u has slept for %d seconds.\n", currpid,i);
		restore(mask);
	}
	mask = disable();
	kprintf("Proc%u finished.\n",currpid);
	restore(mask);
}
