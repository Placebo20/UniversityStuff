#include "knowledge.h"

knowledge::knowledge(int ID, int level_of_knowledge) {
    this->ID = ID;
    this->level_of_knowledge = level_of_knowledge;
}

void knowledge::setLevelOfKnwldg(int level_of_knowledge) {
    this->level_of_knowledge = level_of_knowledge;
}

void knowledge::setIdOfKnwldg(int ID) {
    this->ID = ID;
}

knowledge::knowledge() {

}

knowledge::~knowledge() {

}

int knowledge::getID() {
    return ID;
}

int knowledge::getLvl() {
    return lvl;
}



