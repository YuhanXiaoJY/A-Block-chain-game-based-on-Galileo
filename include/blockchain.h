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
	int slot;				// UDP slot index
	double amount;			// total amount of money (initial value + mining income)
	double miningIncome;	// total amount of income as a miner
};

struct BCdevice{			// available device in the subnet
	int ip;
};

struct BClog bclog[NLOG];
struct BCdevice bcdevice[NDEVICE];
struct BCid bcid;
int bcdevnum;

void BC_init();
void BC_scan();
bool8 BC_transaction(int ip, double amount);
void BC_log();
void BC_cmd();
void BC_handler();

/* tool functions */
void ip2dot(int ip);
void BC_message(char* str, int initiator, int receiver, int mode, double amount);
