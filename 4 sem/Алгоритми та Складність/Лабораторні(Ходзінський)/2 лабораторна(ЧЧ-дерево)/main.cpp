#include <iostream>
#include <regex>
#include <limits>
#include "rbtree.h"
using std::cout;
using std::endl;
using std::cin;

void menu() {
    cout << "1)Insert element" << endl;
    cout << "2)Search for an element" << endl;
    cout << "3)PRE-ORDER Tree-Walk" << endl;
    cout << "4)POST-ORDER Tree-Walk" << endl;
    cout << "5)Remove an element from the tree" << endl;
    cout << "6)Exit" << endl;
    cout << "Your choise -- ";
    return;
}

void inputGroupAndStudents(Group& newGroup) {
    std::regex r("[A-Z a-z А-Я а-я 0-9]*");
    std::string title;
    cout << "Name the Group(use letters and digits): ";
    cin >> title;
     while(!regex_match(title, r)) {
        cout << "You can't use symbols except letters and digits, try again: ";
        cin >> title;
    }
     newGroup.setGroupTitle(title);
     cout << "Now let's create some students." << endl;
     bool stopCreatingStudents = false;
     auto delim = decltype(cin)::traits_type::to_int_type('\n');
     std::string studentName;
     while (!cin.fail() && !stopCreatingStudents) {
         Student* newStudent = new Student();
         std::cout << "Type student's name: ";
         std::getline(cin, studentName);
         if (std::cin.fail())break;
         newStudent->setName(studentName);
         newGroup.addStudent(newStudent);
         std::cout << "Stop creating students?(1 - Yes, 0 - No): ";
         std::cin >> stopCreatingStudents;
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), delim);
     }
}
//Student* newStudent = new Student();
/* newStudent->setName(studentName);
         newGroup.addStudent(newStudent);
         cout << "Stop creating students?(1 - Yes, 0 - No): ";
         cin >> stopCreatingStudents;
         cin.ignore(std::numeric_limits<std::streamsize>::max(), delim);*/

void searchAGroup(RBTree educationalTree) {
    cout << "Enter the title of group y: ";
    std::string title;
    cin >> title;
    Node* temp = educationalTree.getRoot();
    educationalTree.treeSearch(title,temp);
}


void interactiveMode(RBTree& educationalTree) {
    bool quit = false;

    cout << "Hello, thats a realization of Red-Black tree. My subject area is educational department" << endl;
    int choice = 0;
    int input = 0;
    std::string titleToDelete = "\0";
    
    while (!quit) {
        Group* newGroup = new Group();
        menu();
        cin >> choice;
        
        while (choice < 1 || choice > 6 || cin.fail()) {
            cout << "Invalide choice, try again: ";
            cin >> choice;
        }
        switch (choice) {
        case 1:
            inputGroupAndStudents(*newGroup);
            educationalTree.insert(newGroup);
            cout << "You succesfully created a new Node!" << endl;
            break;
        case 2:
            searchAGroup(educationalTree);
            break;
        case 3:
            cout << "Pre-Order tree walk." << endl;
            educationalTree.preorderWalk(educationalTree.getRoot());
            break;
        case 4:
            cout << "Post-Order tree walk." << endl;
            educationalTree.postorderWalk(educationalTree.getRoot());
            break;
        case 5:
            cout << "Enter the title of Group you want to delete: ";
            cin >> titleToDelete;
            educationalTree.remove(titleToDelete, educationalTree.getRoot());
            titleToDelete = "\0";
        case 6:
            quit = true;
            system("cls");
            break;
        default:
            break;
        }    
    }
}

int main()
{       
    RBTree educationalTree;
    interactiveMode(educationalTree);
    return 0;
}