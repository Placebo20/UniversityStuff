#include <iostream>
#include "Classes\helpFunctions.h"
#include <ctime>

void demo() {
    cout << "Hello! Let's create 3 students." << endl;
    student dima = newStudent();
    student misha = newStudent();
    student artem = newStudent();
    cout << "Now let's create a task for them." << endl;
    task task1 = newTask();
    task_process dimatp = newTaskProcess(dima,task1);
    task_process mishatp = newTaskProcess(misha,task1);
    task_process artemtp = newTaskProcess(artem,task1);
    cout << "So, our boys complete the task, so maybe they understand inherent knowledges better" << endl;
    lvlUp(dima,dimatp);
    lvlUp(misha,mishatp);
    lvlUp(artem,artemtp);
    cout << "Now, let's give some task's to dima and look how much time he spends on it" << endl;
    task dtask1 = newTask();
    task dtask2 = newTask();
    task dtask3 = newTask();
    task_process dimatp1 = newTaskProcess(dima,dtask1);
    task_process dimatp2 = newTaskProcess(dima,dtask2);
    task_process dimatp3 = newTaskProcess(dima,dtask3);
    double stime = 0;
    stime += getSpendedTime(dimatp1);
    stime += getSpendedTime(dimatp2);
    stime += getSpendedTime(dimatp3);
    cout << "Spended time == " << stime << endl;
}

int main() {
    srand((unsigned int)(time(NULL)));
    demo();
    return 0;
}
