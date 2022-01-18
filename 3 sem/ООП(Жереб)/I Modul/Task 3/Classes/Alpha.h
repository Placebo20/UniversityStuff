#ifndef TASK_3_ALPHA_H
#define TASK_3_ALPHA_H
#include "Base.h"

class Alpha : Base {
private:
    int N;
    Alpha* pNext;
public:
    Alpha();
    ~Alpha();
    int getAlphaN();
    void setPtr(Alpha* newPtr);
};


#endif //TASK_3_ALPHA_H
