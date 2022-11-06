#ifndef CONCRETE_RECEIVER_H
#define CONCRETE_RECEIVER_H

#include <iostream>
#include <vector>

class Receiver {
	// constructor
	Receiver();
	// take all the data from the recieved vector and store it 
	void storeRecievedData(std::vector<unsigned int>);
	// see if the window size is equal to the vector recieved size to make sure no data was lost
	bool checkLostData(std::vector<unsigned int>);
	// clears the window if all data is recieved. otherwise 
	void alterReceivedVec(std::vector<unsigned int>);


	private:
	std::vector<unsigned int> receivedData;
};

#endif
