#include <iostream>
#include <regex>
#include "splayTree.h"


void menu() {
    std::cout << "1)Insert element" << std::endl;
    std::cout << "2)Search for an element" << std::endl;
    std::cout << "3)Print Tree" << std::endl;
    std::cout << "4)Remove an element from the tree" << std::endl;
    std::cout << "5)Exit" << std::endl;
    std::cout << "Your choise -- ";
    return;
}

void createNewGroup(SplayTree& educationalTree) {
    Group* newGroup = new Group();

    std::cout << "Type the title of group: ";
    std::string titleOfNewGroup;
    std::cin >> titleOfNewGroup;
    std::regex r("[A-Z a-z А-Я а-я 0-9]*");
    while (!regex_match(titleOfNewGroup, r)) {
        std::cout << "You can't use symbols except letters and digits, try again: ";
        std::cin >> titleOfNewGroup;
    }
    newGroup->setGroupTitle(titleOfNewGroup);
    
    std::cout << "Now let's create some students" << std::endl;
    bool stopCreatingStudents = false;
    while (!stopCreatingStudents) {
        Student* newStudent = new Student();
        std::cout << "Type the name of student: ";
        std::string nameOfNewStudent;
        std::getline(std::cin, nameOfNewStudent);
        if (std::cin.fail())break;
        newStudent->setName(nameOfNewStudent);
        newGroup->addStudent(newStudent);
        std::cout << "Stop creating students?(0 - No, 1 - Yes): ";
        std::cin >> stopCreatingStudents;
    }
    educationalTree.insertGroup(newGroup);
    std::cout << "Group " << newGroup->getGroupTitle() << " was created." << std::endl;
}

void findGroup(SplayTree educationalTree) {
    int quantityOfStudents;
    std::cout << "Type the quantity of students in group that you want to find: ";
    std::cin >> quantityOfStudents;
    Node* result = educationalTree.find(quantityOfStudents);
    if (result != nullptr) {
        std::cout << "We found it! Group: " << result->group->getGroupTitle() <<
            " Students: " << result->group->getGroupStudents().size() << std::endl;
    }
}

void deleteGroup(SplayTree& educationalTree) {
    std::cout << "Type the quantity of students in group you want to delete: ";
    int quantityOfStudents;
    std::cin >> quantityOfStudents;
    educationalTree.deleteGroup(quantityOfStudents);
}

void interactiveMode(SplayTree& educationalTree) {
    bool quitTheProgramm = false;

    std::cout << "Hello, thats a realization of Splay tree. My subject area is educational department" << std::endl;
    int choiceMenu = 0;
    menu();
    std::cin >> choiceMenu;
    while (choiceMenu < 1 || choiceMenu > 5) {
        std::cout << "Invalid choice, try again: ";
        std::cin.clear();
        std::cin.ignore(50);
        std::cin >> choiceMenu;
    }
    switch (choiceMenu) {
    case 1:
        std::cout << "Type the title of group: ";
        createNewGroup(educationalTree);
        break;
    case 2:
        std::cout << "Type the quantity of students in group that you want to find: ";
        findGroup(educationalTree);
        break;
    case 3:
        educationalTree.inOrderPrint(true);
        break;
    case 4:
        deleteGroup(educationalTree);
        break;
    case 5:
        quitTheProgramm = true;
        system("cls");
        break;
    default:
        break;
    }
}

int main()
{
    SplayTree educationalTree;
    interactiveMode(educationalTree);
    return 0;
}
