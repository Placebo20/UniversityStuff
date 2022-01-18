#ifndef TASK_1_HELPFUNCTIONS_H
#define TASK_1_HELPFUNCTIONS_H
#include <iostream>
#include "student.h"
#include "task.h"

using namespace std;

void knowledgesHelp() {
    cout << "Knowledges id:\n"
            "[1] Integration\n"
            "[2] Differentiation\n"
            "[3] Finding the Basis\n"
            "[4] Gauss method\n"
            "[5] Supremum and Infinum\n"
            "[6] C-lines\n"
            "[7] Encoder\n"
            "[8] Decoder\n"
            "[9] Phraseological units\n"
            "[10] Teory of sets\n"
            "[11] Teory of automats" << endl;
}

//Creates new student
student newStudent() {
    string name;
    cout << "Let's create a new student, enter his name: ";
    cin >> name;
    student newStudent(name);
    cout << "Now let's add him some knowledges, enter ID, then a mark(from 0 to 5) for that." << endl;
    int isExit = 0;
    knowledgesHelp();
    knowledge newKnowledge;
    while (true) {
        int knwldg;
        cin >> knwldg;
        while (knwldg < 1 || knwldg > 11 || cin.fail()) {
            cout << "Try again.";
            cin >> knwldg;
        }
        int mark = 0;
        cin >> mark;
        while (mark < 1 || mark > 5 || cin.fail()) {
            cout << "Try again.";
            cin >> mark;
        }
        newKnowledge.setIdOfKnwldg(knwldg);
        newKnowledge.setLevelOfKnwldg(mark);
        newStudent.addKnowledge(newKnowledge);
        cout << "Exit? (0 - no, -1 - yes): ";
        cin >> isExit;
        if (isExit == -1)
            break;
    }
    return newStudent;
}

//Creates new task
task newTask(){
    knowledgesHelp();
    int temp;
    cout << "Enter the complexity of task(from 0 to 5):";
    cin >> temp;
    while (temp < 1 || temp > 5 || cin.fail()) {
        cout << "Try again.";
        cin >> temp;
    }
    int mark = 0;
    cin >> mark;
    while (mark < 1 || cin.fail()) {
        cout << "Try again.";
        cin >> mark;
    }
    task tsk(temp,mark);
    while(true){
        int isExit = 0;
        int tmp = 0;
        cout << "Enter the knowledge that need in that task: " << endl;
        cin >> tmp;
        while (tmp < 1 || tmp > 11 || cin.fail()) {
            cout << "Try again.";
            cin >> tmp;
        }
        knowledge knwldg(tmp);
        tsk.setKnowledges(knwldg);
        cout << "Exit? (-1 = yes): ";
        cin >> isExit;
        if(isExit == -1)
            break;
    }
    return tsk;
}

//Creates new task process(Під час виконання завдання визначається отримана кількість балів за завдання (від 0 до максимальної), а також час виконання (в днях): ці параметри залежать від рівня складності завдання, рівня знань студента, що виконує завдання, а також певного випадкового фактору.)
task_process newTaskProcess(student Stdnt, task Tsk) {
    task_process tp;
    int proc = 0;
    proc = tp.checkVectors(Stdnt.getKnowledges(), Tsk.getKnowledges());
    tp.setTakenMark(proc);
    tp.setSpendedTime(proc);
    return tp;
}

//Ups the knowledge after finishing task
student lvlUp(student Stdnt, task_process tp){
    vector<knowledge> temp = Stdnt.getKnowledges();
    int tmp = 0;
    for(int i = 0; i < tp.coincidingIDs.size(); i++){
        tmp = temp[i].getLvl();
        temp[i].setLevelOfKnwldg(tmp + 2);
    }
}

double getSpendedTime(task_process tp) {
    return tp.getSpendedTime();
}

#endif //TASK_1_HELPFUNCTIONS_H
