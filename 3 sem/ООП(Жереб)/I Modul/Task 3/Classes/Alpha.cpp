#include "Alpha.h"


Alpha::Alpha() {
    idGen++;
    N = idGen;
    pNext = nullptr;
}

Alpha::~Alpha() {
    cout << "====================================" << endl;
    cout << "ALPHA DESTRUCTOR" << endl;
    cout << "Object's id(N) is " << getAlphaN() << "." << endl;
    S = S - getAlphaN();
    cout << "S =" << S << endl;
    cout << "====================================" << endl;
}

int Alpha::getAlphaN() {
    return N;
}

void Alpha::setPtr(Alpha *newPtr) {
    pNext = newPtr;
}