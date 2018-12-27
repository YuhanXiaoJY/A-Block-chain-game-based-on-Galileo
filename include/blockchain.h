/* OS-Lab Project: Blockchain Emulator */
#define BCPORT 1024
#define NLOG 1000
#define NDEVICE 50

struct BClog{
	int initiator;			// ip of initiator (use dot)
	int receiver;
	double transaction;		// transaction amount
	bool8 finished;			// whether received messages from both receiver and miner
};


struct BCid{
	int ip;					// ip of myself
	double amount;			// total amount of money (initial value + mining income)
	double miningIncome;	// total amount of income as a miner
};

struct BCdevice{			// available device in the subnet
	int ip;
};

BClog bclog[NLOG];
BCdevice bcdevice[NDEVICE];
BCid bcid;

