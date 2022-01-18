#include "task.h"

task::task(int complexity, int max_mark) {
    this->complexity = complexity;
}

void task::setKnowledges(const knowledge& kn) {
    knowledges.push_back(kn);
}

int task::getMaxMark() {
    return max_mark;
}

int task::getComplexity() {
    return complexity;
}

vector<knowledge> task::getKnowledges() {
    return knowledges;
}

int task_process::checkVectors(vector<knowledge> knowledges1, vector<knowledge> knowledges2) {
    double luck = 0;
    for(int i = 0; i < knowledges2.size(); i++) { // Knowledges of student
        for (int j = 0; j < knowledges1.size(); i++) {//Knowledges that need to complete the task
            if (knowledges2[i].getID() == knowledges1[j].getID()) {
                luck++;
                coincidingIDs.push_back(i);
            }
        }
    }
    return luck / knowledges1.size() * 100 + rand() % 3 + 0;
}

void task_process::setTakenMark(int taken_mark) {
    this->taken_mark = taken_mark;
}

void task_process::setSpendedTime(int taken_mark) {
    this->taken_mark = taken_mark/60;
}

double task_process::getSpendedTime() {
    return spended_time;
}

int task_process::getTakenMart() {
    return taken_mark;
}
