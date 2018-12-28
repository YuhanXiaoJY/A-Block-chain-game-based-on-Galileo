#include<xinu.h>
#include<stdio.h>

void BC_scan()
{
	uint32	ipaddr;			/* IP address in binary		*/
	int32	retval;			/* return value			*/
	int32	slot;			/* Slot in ICMP to use		*/
	static	int32	seq = 0;	/* sequence number		*/
	char	buf[56];		/* buffer of chars		*/
	int32	i;			/* index into buffer		*/
	int32	nextval;		/* next value to use		*/

	bcdevnum = 0;
	char args[256][50];
	bool8 flags[256];
	int32 ip;
	ip = getlocalip();
	for(i = 100; i<110; i++)
	{
		sprintf(args[i], "%d.%d.%d.%d", (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff
								,i);
		flags[i] = 0;
		/* convert argument to binary */

		retval = dot2ip(args[i], &ipaddr);
		if ((int32)retval == SYSERR) {
			fprintf(stderr, "%s: invalid IP address\n", args[i]);
			continue;
		}

		/* Register to receive an ICMP Echo Reply */

		slot = icmp_register(ipaddr);
		if (slot == SYSERR) {
			fprintf(stderr,"%s: ICMP registration failed\n", args[i]);
			continue;
		}

		/* Fill the buffer with values - start with low-order byte of	*/
		/*	the sequence number and increment			*/

		nextval = seq;
		int j =0;
		for (j = 0; j<sizeof(buf); j++) {
			buf[j] = 0xff & nextval++;
		}

		/* Send an ICMP Echo Request */
		retval = icmp_send(ipaddr, ICMP_ECHOREQST, slot,
						seq++, buf, sizeof(buf));
		if (retval == SYSERR) {
			fprintf(stderr, "Ping:%s no response from host.\n", args[i]);
			icmp_release(slot);
			continue;
		}

		/* Read a reply */

		retval = icmp_recv(slot, buf, sizeof(buf), 3000);
		icmp_release(slot);
		if (retval == TIMEOUT) {
			fprintf(stderr, "Ping:%s time out.\n",
					args[1]);
			continue;
		}

		if (retval != sizeof(buf)) {
			fprintf(stderr,"expected %d bytes but got back %d\n",
				sizeof(buf), retval);
			}
		fprintf(stderr, "host %s is alive\n", args[i]);
		flags[bcdevnum] = i;
		dot2ip(args[i], &bcdevice[bcdevnum].ip);
		bcdevnum++;

	}

	kprintf("Start-------------------------------\n");
	kprintf("The device list:\n");
	for(i = 0; i<bcdevnum; i++)
	{

		kprintf("%3d %s\n", i, args[flags[i]]);
	}

	
}