#ifndef CONCRETE_RECEIVER_H
#define CONCRETE_RECEIVER_H

#include "ConcreteSender.h"
#include <iostream>
#include <vector>

class Receiver {
	public:
	// constructor
	Receiver();
	// take all the data from the recieved vector and store it 
	void storeReceivedData(std::vector<unsigned int>);
	// see if the window size is equal to the vector recieved size to make sure no data was lost
	bool checkLostData(std::vector<unsigned int>, Sender);

	void alterReceivedVec(std::vector<unsigned int>, Sender);
	// clears the window if all data is recieved. otherwise 
	void sendBackUnackData(std::vector<unsigned int>, Sender);
	std::vector<unsigned int> receivedData;

	private:
	std::vector<unsigned int> cache;
};

#endif
