#ifndef CONCRETE_HEADER_H #define CONCRETE_HEADER_H

#include <cstdint>
#define HEADER_SZ 4
#define DATA_SZ 1024 

struct simplepacket {
	uint8_t header[HEADER_SZ];
	char data[DATA_SZ]; // payload 
};

class ConcreteHeader {
	public: 
		// default constructor that initializes header to 0
		ConcreteHeader();
		void setType(unsigned int t); // 2 bits and must be <= 3 
	       	unsigned int getType() const;
		void setTR(unsigned int t); // 1 bit bool 
		unsigned int getTR() const;
		void setWindow(unsigned int t); // 5 bits and <= 31 
		unsigned int getWindow() const;
		void setSeqNum(unsigned int t);  //  header is 8 - 15
		unsigned int getSeqNum() const;
		void setLen(unsigned int t);
		unsigned int getLen() const; // 16 bits

		void * thePacket() {
			return &packet;
		} // returns pointer to structure holding the packet including the headers 
		void * theLeng() { 
			return packet.data;
		}
	private:
		struct simplepacket packet;
		// start index of val header field 
		const int VL = 0;
		const int LEN = 2;
	
};	


#endif
