#ifndef TASK_3_BASE_H
#define TASK_3_BASE_H
#include "iostream"
#include "vector"
using namespace std;

extern int S;
static int idGen;

class Base {
private:
    int N;
    Base* current;
    Base* pNext;
public:
    Base();
    ~Base();
    int getBaseN();
    void setPtr(Base* newPtr);
};


#endif //TASK_3_BASE_H
