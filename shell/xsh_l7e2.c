/* xsh_l7e2 */
/*
	exercise2 of lab7
	Implemention of a mechanism for a process to capture the exceptions
	during execution.
*/

#include <xinu.h>

#define catch out:
#define mytry setjmp(&&out);
#define endtry ;

shellcmd xsh_l7e2(int nargs, char *args[])
{
	kprintf("execute a = 100 / 0\n");
	mytry{
		int a = 100/0;
	}catch{
		kprintf("100/0 exception captured!\n");
		exit();
	}
	endtry
	return 0;
}
