/* xsh_l4e3 ttyread - */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_l4e3
 *------------------------------------------------------------------------
 */
/*void proc1(void);
void proc2(void);*/

shellcmd xsh_l4e3(int nargs, char *args[])
{

	/*pid32 pid1,pid2;
	pid1 = create(proc1, 1024, 10, "proc1", 0);
	pid2 = create(proc2, 1024, 10, "proc2", 0);
	resume(pid1);
	resume(pid2);
	sleep(8);*/
	
	return 0;
}
/*void proc1()
{
	ttycontrol(&devtab[CONSOLE],TC_MODEC,1,1);
	//kprintf("Proc1 is running now.\n");
	int retval1;
	char buffer[3001];
	int i;
	//for(i=0;i<3000;i++)
		//buffer[i] = '1';
	//buffer[3000] = '\0';
	//char buffer[100] ;
	retval1 = ttyread(&devtab[CONSOLE],buffer, 3001);
	buffer[retval1-1] = '\0';
	intmask mask = disable();
	kprintf("retval1: %d\n", retval1);
	kprintf("buffer1: %s", buffer);
	restore(mask);

}

void proc2()
{
	ttycontrol(&devtab[CONSOLE],TC_MODEC,1,1);
	//kprintf("Proc2 is running now.\n");
	int retval2;
	char buffer[3001];
	int i;
	//for(i=0;i<3000;i++)
		//buffer[i] = '2';
	//buffer[3000] = '\0';
	//char buffer[100] = "proc2 write\n";
	retval2 = ttyread(&devtab[CONSOLE],buffer, 3001);
	buffer[retval2-1] = '\0';
	intmask mask = disable();
	kprintf("retval2: %d\n", retval2);
	kprintf("buffer2: %s", buffer);
	restore(mask);

}*/
