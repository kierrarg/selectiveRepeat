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

bool Receiver::checkLostData(std::vector<unsigned int> r) {
    if (r.size() == windowSize) {
        return True;
    }
    else {
        return False;
    }
}

void Receiver::alterReceivedVec(std::vector<unsigned int> r) {
    if (checkLostData(std::vector<unsigned int> r)) {
        r.clear();
    }
    else {
        sendBackUnackData(std::vector<unsigned int> r);
    }
}

void Receiver::sendBackUnackData(std::vector<unsigned int> r) {
    for (int i = 0; i < r.size(); i++) {
        cache.push_back(r[i]);
    }

    for (int i = 0; i < window.size(); i++) {
        if (cache[i] == window[i]) {
            window.erase(window.begin() + i);
        }
    }
}
