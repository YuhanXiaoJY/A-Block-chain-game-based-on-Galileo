#include <xinu.h>

shellcmd xsh_l6e1(int nargs, char *args[])
{
	char * dskname = "rds1\0";
	struct dentry * devptr;
	devptr = (struct dentry *)&devtab[RDISK]; 
	int retval;
	retval = rdsopen(devptr,dskname,"rw");
	rdsclose(devptr);
}
