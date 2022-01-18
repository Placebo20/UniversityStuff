#include "Red.h"

Red::Red() {
    idGen++;
    N = idGen;
}

Red::~Red() {
    cout << "====================================" << endl;
    cout << "RED DESTRUCTOR" << endl;
    cout << "Object's id(N) is " << getRedN() << "." << endl;
    S = S + getRedN() / 2;
    cout << "S =" << S << endl;
    cout << "====================================" << endl;
}

int Red::getRedN() {
    return idGen;
}
