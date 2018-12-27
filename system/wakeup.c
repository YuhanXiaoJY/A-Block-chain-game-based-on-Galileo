/* wakeup.c - wakeup */

#include <xinu.h>
//uint32 callwait;
//sid32 s_wait;
/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	
	/* Awaken all processes that have no more time to sleep */
	/*//if call wait	
	if(callwait == 1)
	{
		intmask mask;
		mask = disable();
		kprintf("%d uses wakeup to call wait.------\n", currpid);
		restore(mask);
		wait(s_wait);
	}
	//if call wait*/

	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		//my trace
		if(isWakeup == 1)
		{
			pid32 p;
			p = firstid(sleepq);
			intmask mask1;
			mask1 = disable();
			kprintf("Proc%u is waken up.\n",p);
			restore(mask1);
			isWakeup = 0;
		}
		//my trace
		ready(dequeue(sleepq));
	}

	resched_cntl(DEFER_STOP);
	return;
}
