#ifndef TASK_1_STRATEGIES_H
#define TASK_1_STRATEGIES_H
#include "student.h"
#include "task.h"

void startEasiest(vector<task> tsk, student stdnt){
    vector<knowledge> temp1 = stdnt.getKnowledges(); //способности студента
    vector<int> tmp;
    for(int i = 0; i < tsk.size(), i++){
        vector<knowledge> temp2 = tsk[i].getKnowledges();
        for(int j = 0; j < tsk.size(), j++){
            for(int k = 0; k < temp1.size(); k++){
                for(int o = 0; o < temp2.size(); o++){
                    if(temp1[k].getID() == temp2[o].getID()){
                        tmp[j]++;
                    }
                }
            }
        }
    }
}

#endif //TASK_1_STRATEGIES_H
