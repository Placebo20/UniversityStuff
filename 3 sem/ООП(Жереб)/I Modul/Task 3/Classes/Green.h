#ifndef TASK_3_GREEN_H
#define TASK_3_GREEN_H
#include "Alpha.h"
#include "Base.h"

class Green : Alpha{
private:
    int N;
    Green* pNext;
public:
    Green();
    ~Green();
    int getGreenN();
    void setPtr(Green* ptr);
};


#endif //TASK_3_GREEN_H
