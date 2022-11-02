#include "ConcreteHeader.h"

ConcreteHeader::ConcreteHeader() {
	packet.header[0] = packet.header[1] = packet.header[2] = packet.header[3] = 0; // need to include a new packet header
}

void ConcreteHeader::setType(unsigned int t) {
	//clear the val first
	packet.header[VL] &= 0x3f; // 0011 1111 keep these bits and change 0s

	// sets lowest 2 bits to header field, does not disturb other bits 
	if (t > 3) {
		packet.header[VL] = (0 << 6); // bit shift
	} else {
		packet.header[VL] |= (t << 6);
	}
}

unsigned int ConcreteHeader::getType() const{
	return (packet.header[VL] >> 6);
}

void ConcreteHeader::setTR(unsigned int t) {
	packet.header[VL] &= 0xdf; // 1101 1111
	t &= 0x1; // ensures value is only a 1 or 0
	packet.header[VL] |= (t << 5); // changes TR bit
}

unsigned int ConcreteHeader::getTR() const{
	return ((packet.header[VL] & 0x20) >> 5); // 1000 0000
}

void ConcreteHeader::setWindow(unsigned int t) {
	packet.header[VL] &= 0xe0; // 1110 0000
	t &= 0x1f; // 0001 1111
	packet.header[VL] |= (t);
	
}

unsigned int ConcreteHeader::getWindow() const{
	return ((packet.header[VL] & 0x1f)); // 0001 1111
}

void ConcreteHeader::setSeqNum(unsigned int t) {
	t &= 0xff; // 1111 1111
	packet.header[1] = t; // accesses second byte of header	
}

unsigned int ConcreteHeader::getSeqNum() const{
	return packet.header[1];

}

void ConcreteHeader::setLen(unsigned int t) {
	packet.header[LEN] = (t >> 8);
	packet.header[LEN + 1] = (t&255);
}

unsigned int ConcreteHeader::getLen() const {
	return packet.header[LEN + 1] | (packet.header[LEN] << 8);
}



