/* clkhandler.c - clkhandler */

#include <xinu.h>

uint32 isPreempt;
uint32 isWakeup;
/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	//l5e4
	int i;
	
	for(i=1; i<ARP_SIZ; i++)
	{
		if(arpcache[i].arstate != AR_FREE)
		{
			arpcache[i].arptime++;
			if(arpcache[i].arptime >= 10000 )
			{
				arpcache[i].arptime = 0;
				arpcache[i].arstate = AR_FREE;
				kprintf("arpcache[%d] times out!\n", i);
				kprintf("ARP_SIZ: %d\n", ARP_SIZ);
			}
		}
	}
	//l5e4

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			//my trace
			if(Trace == 1)
				isWakeup = 1;
			//my trace
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		//my trace
		if(Trace == 1)
			isPreempt = 1;
		//my trace
		resched();
	}
}
