#ifndef CONCRETE_SENDER_H
#define CONCRETE_SENDER_H

#include <iostream>
#include <vector>

class Sender {
	public: 
	// constructor, n represents # of bits for sequence nums 
	Sender();
	// true if the window isn't full
	bool canAddNew();
	// void function that updates the vector
	int addNew();
	// sets max size of sliding window  
	void setWinSize(int s); 
	// returns # unacknowledged sequences 
	int nrSeqInWin();
	// returns the window size
	int getWinSize();
	// returns the window
	std::vector<unsigned int> getWindow();
	// overwrites the window with a new vector
	void overwriteWindow(std::vector<unsigned int> newWin);
	private: 
	std::vector<unsigned int> sequence;
	std::vector<unsigned int> window;
	int windowSize;

};

#endif
