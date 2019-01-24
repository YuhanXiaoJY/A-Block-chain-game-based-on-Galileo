# A-Block-chain-game-based-on-Galileo
### Description  
This is a project for OS-lab.
Our goal is to implement a little game which simulates the transactions in blockchain, based on a embedded system called Xinu. You can
download Xinu from https://xinu.cs.purdue.edu/  

### Details  

The game is very easy to understand. Everyone linked in a net is endowed with ￥100 and can transact with each other. The one who initiate
the transaction acts as an initiator and must send a valid number of money to another device. The receiver cannot get the money at once. Only
 when a miner agrees to help with the transaction can we call it a success: the initiator's balance is reduced and the receiver get the money
 successfully.
 Every device in the net can behave as initiator, receiver or a miner. In order to coordinate transactions, a protocol criterion is needed 
 when the devices send messages to each other.

Protocal types：
​	

| protocal | initiator     | receiver           | annotation               |
| ---- | ---------- | ---------------- | ------------------ |
| 1    | initiator | receiver       | initiate a transction     |
| 2    | receiver | all devices in the subnet | wait for a miner to handle the transaction   |
| 3    | miner       | receiver       | miner agrees to handle the transaction       |
| 4    | receiver | miner             | confirm the miner |
| 5    | miner       | initiator       | broadcast: the transaction is done     |
| 6    | miner       | all devices in the subnet       | broadcast: the transaction is done     |
| 6    | receiver | all devices in the subnet       | broadcast: the transaction is done     |


### Team members
Yuhan Xiao, Dongwei Xiang
