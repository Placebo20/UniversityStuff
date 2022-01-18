#include <iostream>
#include <vector>
#include "bPlusTree.h"
#include "group.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, Group* group) {
    os << group->getGroupTitle() << " | Count of Students: " << group->getGroupStudents().size();
    return os;
}

void example_Group() {//функція для тестування алгоритмів роботи з B+ -деревом
    vector<Group> students;
    cout << "Enter num car in B+ tree\n  n =";
    int n;
    cin >> n;
    cout << endl;

    BPlusTree<Group> tree(3);
    Group group;
    string name;
    for (int i = 0; i < n; i++) {
        cout << "Set title of group: ";
        cin >> name;
        group.setGroupTitle(name);
        group.addStudents();
        tree.insert(group);

    }
    tree.print(cout);
    cout << endl << endl;
    tree.printSorted(cout);
    cout << endl << endl;

    cout << "Enter  name car for remove = ";
    cin >> name;

    tree.remove(group);

    cout << endl << endl;
    tree.print(std::cout);
}
int main()
{
    example_Group();
    return 0;
}


