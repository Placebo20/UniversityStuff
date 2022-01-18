#ifndef TASK_3_RED_H
#define TASK_3_RED_H
#include "Alpha.h"
#include "Base.h"

class Red : Alpha {
private:
    int N;
    Red* pNext;
public:
    Red();
    ~Red();
    int getRedN();
    void setPtr(Red* ptr);
};


#endif //TASK_3_RED_H
