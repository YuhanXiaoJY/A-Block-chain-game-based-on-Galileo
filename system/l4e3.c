#include <xinu.h>
void proc1(int id);

void l4e3()
{

	pid32 pid1,pid2;
	pid1 = create(proc1, 1024, 60, "proc1", 1,1);
	pid2 = create(proc1, 1024, 65, "proc2", 1,2);
	resume(pid1);	
	resume(pid2);
	//sleep(8);
	
}
void proc1(int id)
{

	int retval1;
	char buffer[3001];

	retval1 = ttyread(&devtab[CONSOLE],buffer, 3001);
	sleep(3);

	intmask mask = disable();
	kprintf("retval %d: %d\n", id,retval1);
	kprintf("buffer %d: %s", id,buffer);
	restore(mask);

}


