#ifndef TASK_1_STUDENT_H
#define TASK_1_STUDENT_H
#include <memory>
#include "knowledge.h"

class student {
protected:
    string name;
    vector<knowledge> sknowledges;
public:
    student(string name);
    ~student();
    void addKnowledge(const knowledge& kn);
    void setLvlById(int ID, int lvl);
    vector<knowledge> getKnowledges();
    string getName();
};


#endif //TASK_1_STUDENT_H
