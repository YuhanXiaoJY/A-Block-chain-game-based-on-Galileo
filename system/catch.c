/* catch.c */

#include<xinu.h>

struct jmpent jmptab[NPROC];

int setjmp(int32 ** addr)
{
	intmask mask;
	struct jmpent* jmpptr;

	mask = disable();
	jmpptr = &jmptab[getpid()];
	jmpptr->valid = TRUE;
	jmpptr->mask = mask;
	jmpptr->addr = addr;
	restore(mask);
	kprintf("return address set: 0x%08X\n", addr);
	return 0;
}

void longjmp()
{
	intmask mask;
	struct jmpent* jmpptr;
	
	kprintf("enter longjump successfully.\n");
	mask = disable();
	jmpptr = &jmptab[getpid()];

	if (!jmpptr->valid)
	{
		restore(mask);
		return;
	}
	else
	{
		kprintf("return to original function 0x%08X\n", jmpptr->addr);
		goto *(jmpptr->addr);
	}
}
