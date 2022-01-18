#ifndef TASK_3_BETA_H
#define TASK_3_BETA_H
#include "Base.h"

class Beta : Base {
private:
    int N;
    Base* pNext;
public:
    Beta();
    ~Beta();
    int getBetaN();
    void setPtr(Beta* ptr);
};


#endif //TASK_3_BETA_H
