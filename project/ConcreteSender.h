#ifndef CONCRETE_SENDER_H
#define CONCRETE_SENDER_H

#include <iostream>
#include <vector>

class Sender() {
	public: 
	// constructor, n represents # of bits for sequence nums 
	Sender();
	// true if the window isn't full
	bool canAddNew();
	// void function that updates the vector
	void addNew();
	// sets max size of sliding window  
	void setWinSize(int s); 
	// acknowledgment for s is received 	
	void acknowledge(unsigned int s);
	// returns # unacknowledged sequences 
	int nrSeqInWin();
	// returns the window
	std::vector getWindow();
	private: 
	std::vector<unsigned int> sequence;
	std::vector<unsigned int> window;
	int windowSize;

};

#endif
