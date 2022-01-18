#include "Green.h"

Green::Green() {
    idGen++;
    N = idGen;
    pNext = nullptr;
}

Green::~Green() {
    cout << "====================================" << endl;
    cout << "GREEN DESTRUCTOR" << endl;
    cout << "Object's id(N) is " << getGreenN() << "." << endl;
    S = S-getGreenN()/2 + 14;
    cout << "S =" << S << endl;
    cout << "====================================" << endl;
}

int Green::getGreenN() {
    return N;
}

void Green::setPtr(Green *ptr) {
    pNext = ptr;
}
