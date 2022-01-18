#ifndef TASK_1_KNOWLEDGE_H
#define TASK_1_KNOWLEDGE_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class knowledge {
protected:
    int ID;
    int level_of_knowledge; //Level of knowledge from 0 to 5
public:
    knowledge();
    explicit knowledge(int ID, int level_of_knowledge = 0);
    void setIdOfKnwldg(int ID);
    void setLevelOfKnwldg(int level_of_knowledge);
    ~knowledge();
    int getID();
    int getLvl();
};


#endif //TASK_1_KNOWLEDGE_H
