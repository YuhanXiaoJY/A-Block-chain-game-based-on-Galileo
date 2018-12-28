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

struct BC_ilog{
	int initiator;			// ip of initiator (use dot)
	int receiver;
	double transaction;		// transaction amount
	bool8 isok;				// whether the transaction is ok
};

struct BC_rlog{
	int initiator;			// ip of initiator (use dot)
	int receiver;
	int miner;
	double transaction;		// transaction amount
	bool8 isok;				// whether the transaction is ok
	bool8 waiting;			// waiting for miner
};

struct BC_mlog{
	int initiator;			// ip of initiator (use dot)
	int receiver;
	double transaction;		// transaction amount
	bool8 isok;
	int progress;
};

struct BCid{
	int ip;					// ip of myself
	int slot;				// UDP slot index
	double amount;			// total amount of money (initial value + mining income)
	double miningIncome;	// total amount of income as a miner
};

struct BCdevice{			// available device in the subnet
	uint32 ip;
};

struct BClog bclog[NLOG];
struct BC_ilog bc_ilog[NLOG];
struct BC_rlog bc_rlog[NLOG];
struct BC_mlog bc_mlog[NLOG];
struct BCdevice bcdevice[NDEVICE];
struct BCid bcid;
int nbclog, nbc_ilog, nbc_rlog, nbc_mlog;
int bcdevnum;

void BC_init();
void BC_scan();
bool8 BC_transaction(int ip, double amount);
void BC_logging();
void BC_ilogging();
void BC_rlogging();
void BC_mlogging(); 
void BC_cmd();
void BC_handler();

/* tool functions */
void ip2dot(int ip, char * a);
void BC_message(char* str, int initiator, int receiver, int mode, double amount);
bool8 BC_decode(char * str, int len, int *initiator, int *receiver, int *mode, double *amount);