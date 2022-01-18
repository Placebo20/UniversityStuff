#include <iostream>
#include <string>
#include <vector> 
#include "binHeap.h"
#include "group.h"

int main() {

    std::vector<std::string> groups = { "K11","K12","K13","K14"," K15","K16","K17","K18" };
    BinominalHeap<std::string> tree1;
    for (int i = 0; i < 8; i++)
        tree1.insert(groups[i]);
    std::cout << "NEW TREE\n";
    tree1.print();

    std::cout << "EXTRACT MIN\n";
    tree1.extractMin();
    tree1.print();
    std::cout << "\n \n \n \n ---------------------------------------------\n \n ";

    BinominalHeap<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insert(i);
    std::cout << "NEW TREE\n";
    tree.print();

    std::cout << "EXTRACT MIN\n";
    tree.extractMin();
    tree.print();
    return 0;
}