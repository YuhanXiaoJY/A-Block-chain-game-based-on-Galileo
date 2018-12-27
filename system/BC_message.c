#include <xinu.h>
void BC_message(char* str, int initiator, int receiver, int mode, double amount){
	char initiator_dot[20];
	char receiver_dot[20];
	ip2dot(initiator, initiator_dot);
	ip2dot(receiver, receiver_dot);
	sprintf(str, "%s_%s_%d_%f", initiator_dot, receiver_dot, mode, amount);
}
