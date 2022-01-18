#ifndef TASK_1_TASK_H
#define TASK_1_TASK_H
#include "knowledge.h"
#include "student.h"

class task {
protected:
    int complexity; // 1 to 5 where 1 is easiest and 5 is hardest
    vector<knowledge> knowledges;
    int max_mark; //maximum mark for task;
public:
    task(int complexity, int max_mark);
    int getMaxMark();
    int getComplexity();
    vector<knowledge> getKnowledges();
    void setKnowledges(const knowledge& kn);

};

class task_process{
private:
    int taken_mark;
    double spended_time; //in days
public:
    vector<int> coincidingIDs;
    int checkVectors(vector<knowledge> knowledges1, vector<knowledge> knowledges2);
    void setTakenMark(int taken_mark);
    void setSpendedTime(int taken_mark);
    int getTakenMart();
    double getSpendedTime();
};


#endif //TASK_1_TASK_H
