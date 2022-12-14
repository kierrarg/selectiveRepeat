#include "ConcreteSender.h"
#include <vector>

Sender::Sender() {
    windowSize = 0;
    sequence.push_back(1);
    sequence.push_back(2);
    sequence.push_back(3);

}

bool Sender::canAddNew() {
    if (window.size() < windowSize)
        return true;
    else
        return false;
}

int Sender::addNew() {
    if (canAddNew()) {
        int a = sequence.front();
        sequence.erase(sequence.begin());
        window.push_back(a);
        return a;
    } else {
        return -1;
    }
}

void Sender::setWinSize(int s) {
    windowSize = s;
}


int Sender::getWinSize() {
  return windowSize;
}

std::vector<unsigned int> Sender::getWindow() {
  return window;
}

void Sender::overwriteWindow(std::vector<unsigned int> newWin) {
    window = newWin;
}


