#include "Beta.h"

Beta::Beta() {
    idGen++;
    N = idGen;
    pNext = nullptr;
}

Beta::~Beta() {
    cout << "====================================" << endl;
    cout << "BETA DESTRUCTOR" << endl;
    cout << "Object's id(N) is " << getBetaN() << "." << endl;
    S = S + 3*getBetaN() + 30;
    cout << "S =" << S << endl;
    cout << "====================================" << endl;
}

int Beta::getBetaN() {
    return N;
}

void Beta::setPtr(Beta* ptr){
    pNext = ptr;
}
