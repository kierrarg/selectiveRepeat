#include "ConcreteReceiver.h"
#include "ConcreteSender.h"
#include <vector>

Receiver::Receiver() {

}

void Receiver::storeRecievedData(std::vector<unsigned int> r) {
    for (int  i = 0; i < r.size(); i++){
        receivedData.push_back(r[i]);
    }
}

bool Receiver::checkLostData(std::vector<unsigned int> r, Sender s) {
    if (r.size() == s.windowSize) {
        return true;
    }
    else {
        return false;
    }
}

void Receiver::alterReceivedVec(std::vector<unsigned int> r, Sender s) {
    if (checkLostData(r, s)) {
        r.clear();
    }
    else {
        sendBackUnackData(r, s);
    }
}

void Receiver::sendBackUnackData(std::vector<unsigned int> r, Sender s) {
    for (int i = 0; i < r.size(); i++) {
        cache.push_back(r[i]);
    }

    for (int i = 0; i < s.window.size(); i++) {
        if (cache[i] == s.window[i]) {
            s.window.erase(s.window.begin() + i);
        }
    }
}
