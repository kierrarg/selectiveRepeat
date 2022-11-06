#include "ConcreteHeader.h"
#include "ConcreteSender.h"
#include "ConcreteReceiver.h"
#include "gtest/gtest.h"  // google test framework
#include <vector>

class HeaderTest : public testing::Test {
protected:
  ConcreteHeader * h_;

  void SetUp() override {
    h_ = new ConcreteHeader;  // create a new class before each test to start fresh
  }

  void TearDown() override {
    delete h_;
  }
};

// testing get len
TEST_F(HeaderTest, setLength) {
  h_->setLen(0x1234);
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ASSERT_TRUE(ptr->header[2] == 0x12);
  ASSERT_TRUE(ptr->header[3] == 0x34);
}

TEST_F(HeaderTest, getHeader) {
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->header[2] = 0x56;
  ptr->header[3] = 0xa2;
  ASSERT_TRUE(h_->getLen() == 0x56a2);
}

// testing set type 
TEST_F(HeaderTest, testSetType) {
  // get a pointer to the packet.
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  // initialize the first byte to some value.
  ptr->header[0] = 0x2e;
  h_->setType(2);
  ASSERT_TRUE(ptr->header[0] == 0xae);
}


// testing get type
TEST_F(HeaderTest, getType) {
 struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
 ptr->header[0] = 0x2e;
 h_->setType(2);
 ASSERT_TRUE(h_->getType() == 2);
}

TEST_F(HeaderTest, setVal) {
 struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
 ptr->header[0] = 0x2e;
 h_->setType(4);
 ASSERT_TRUE(ptr->header[0] == 0x00);
}

// testing set TR 
TEST_F(HeaderTest, setTR) {
struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
ptr->header[0] = 0xdf;
h_->setTR(1);
ASSERT_TRUE(ptr->header[0] == 0xff);
}

// testing get TR
TEST_F(HeaderTest, getTR) {
struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
ptr->header[0] = 0xdf;
h_->setTR(1);
ASSERT_TRUE(h_->getTR() == 1);
}

// testing set window 
TEST_F(HeaderTest, setWindow) {
struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
ptr->header[0] = 0x0;
h_->setWindow(12);
ASSERT_TRUE(ptr->header[0] == 0x0c);
}

// testing get window 
TEST_F(HeaderTest, getWindow) {
struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
ptr->header[0] = 0xe0;
h_->setWindow(3);
ASSERT_TRUE(h_->getWindow() == 3);
}

// testing set seq num 
TEST_F(HeaderTest, setSeqNum) {
struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
ptr->header[1] = 0x00;
h_->setSeqNum(255);
ASSERT_TRUE(ptr->header[1] == 0xff);
}

// testing get seq num 
TEST_F(HeaderTest, getSeqNum) {
struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
ptr->header[1];
h_->setSeqNum(255);
ASSERT_TRUE(h_->getSeqNum() == 255);
}


class SenderTest : public testing::Test {
	protected:
		Sender * s;

		void SetUp() override {
			s = new Sender;
		}

		void TearDown() override {
			delete s;
		}
};

TEST_F(SenderTest, canAddNew) {
	s->setWinSize(3);
	int b = s->addNew();
	ASSERT_TRUE(b == 1);
	b = s->addNew();
	ASSERT_TRUE(b == 2);
	b = s->addNew();
	ASSERT_TRUE(b == 3);
}

// testing can add new function 
TEST_F(SenderTest, canAddNewF) {
	bool b = s->canAddNew();
	EXPECT_FALSE(b);
}

// testing add new frame 
TEST_F(SenderTest, addNew) {
	s->setWinSize(2);
	int i = s->addNew();
	ASSERT_TRUE(i == 1);
	i = s->addNew();
	ASSERT_TRUE(i == 2);
}
// sets max size of sliding window
TEST_F (SenderTest, setWinSize) {
	ASSERT_TRUE(s->getWinSize() == 0);
	s->setWinSize(2);
	ASSERT_TRUE(s->getWinSize() == 2);
}
//returns the window size
TEST_F (SenderTest, getWinSize) {
	s->setWinSize(2);
	ASSERT_TRUE(s->getWinSize() == 2);
}



class ReceiverTest : public testing::Test {
	protected:
		Receiver * r;
		Sender * s_;

		void SetUp() override {
			r = new Receiver;
			s_ = new Sender;
		}

		void TearDown() override {
			delete r;
			delete s_;
		}
};

//take all data from received vector and store it
TEST_F (ReceiverTest, storeReceivedData) {
	std::vector<unsigned int> i;
       	i.push_back(1);
	r->storeReceivedData(i);
	EXPECT_EQ(r->receivedData.size(), i.size());	
}
//checks to see if data was lost
TEST_F (ReceiverTest, checkLostData) {
	std::vector<unsigned int> i;
	i.push_back(1);
	Sender s;
	s.setWinSize(1);
	EXPECT_TRUE(r->checkLostData(i, s) == true);
}
//clears window
TEST_F (ReceiverTest, alterReceivedVec){
	std::vector<unsigned int> i;
	i.push_back(1);
	Sender s;
	s.setWinSize(1);
	r->alterReceivedVec(i, s);
	EXPECT_EQ(i.size(), 1);
}
//sends back unacknowledged data
TEST_F (ReceiverTest, sendBackUnackData) {
	std::vector<unsigned int> i;
	i.push_back(1);
	Sender s;
	s.window.push_back(1); 
	r->sendBackUnackData(i, s);
	EXPECT_EQ(s.window.size(), 1);
}

