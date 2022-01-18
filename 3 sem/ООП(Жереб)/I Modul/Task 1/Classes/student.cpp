#include "student.h"

student::student(string name){
    this->name = name;
}

student::~student() {

}

void student::addKnowledge(const knowledge &kn) {
    sknowledges.push_back(kn);
}

string student::getName() {
    return name;
}

vector<knowledge> student::getKnowledges() {
    return sknowledges;
}

void student::setLvlById(int ID, int lvl) {
    getKnowledges()[ID].setLevelOfKnwldg(lvl);
}



