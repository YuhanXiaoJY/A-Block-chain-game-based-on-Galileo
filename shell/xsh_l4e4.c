/* xsh_l4e4 take control of CONSOLE - */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_l4e4
 *------------------------------------------------------------------------
 */
//extern sid32 con_sem;
//void proc1(void);
//void proc2(void);
//intmask mask;
shellcmd xsh_l4e4(int nargs, char *args[])
{
	/*int i;
	//for(i=0;i<20;i++)
		//con_sem[i]= semcreate(1)
	con_sem = semcreate(1)
	//wait(con_sem);
	pid32 pid1,pid2;
	pid1 = create(proc1, 1024, 15, "proc1", 0);
	pid2 = create(proc2, 1024, 10, "proc2", 0);
	resume(pid1);
	resume(pid2);*/

	
	return 0;
}
/*void proc1()
{
	
	getControl();
	char buffer[100] = "chars of proc1";
	int retval = ttywrite(&devtab[CONSOLE], buffer, 100);
	buffer[retval-1] = '\0';
	kprintf("retval1: %d\n", retval);
	kprintf("buffer1: %s\n", buffer);
	yieldControl();
}
void getControl()
{
	mask = disable();
	wait(con_sem);
}
void yeildControl()
{
	signal(con_sem);
	restore(mask);
}
void proc2()
{
	char buffer[100] = "chars of proc2";
	kprintf("proc2 is gonging to read\n");
	int retval = ttywrite(&devtab[CONSOLE], buffer, 100);
	buffer[retval-1] = '\0';
	kprintf("retval2: %d\n", retval);
	kprintf("buffer2: %s\n", buffer);
}*/
