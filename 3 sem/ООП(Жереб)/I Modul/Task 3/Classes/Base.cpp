#include "Base.h"

int S = 0;

Base::Base() {
    idGen++;
    N = idGen;
    pNext = nullptr;
}

Base::~Base() {
    cout << "====================================" << endl;
    cout << "BASE DESTRUCTOR" << endl;
    cout << "Object's id(N) is " << getBaseN() << "." << endl;
    S = 2*S + getBaseN() - 30;
    cout << "S == " << S << endl;
    cout << "====================================" << endl;
}

int Base::getBaseN() {
    return N;
}

void Base::setPtr(Base* newPtr) {
    pNext = newPtr;
}

