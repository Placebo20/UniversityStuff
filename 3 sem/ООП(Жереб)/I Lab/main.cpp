#include "Trees/Trees.h"
int main() {
    //chooseTree();
    BinarySearchTree obj(0,0,0,0,0,0);
    obj.append(-7,-7,-7,-7,-7,-7);
    obj.append(-10,-10,-10,-10,-10,-10);
    obj.append(-5,-5,-5,-5,-5,-5);
    obj.append(-4,-4,-4,-4,-4,-4);
    obj.append(6,6,6,6,6,6);
    obj.append(4,4,4,4,4,4);
    obj.append(4,4,4,4,4,4);
    obj.append(7,7,7,7,7,7);
    obj.append(32,32,32,32,32,32);
    obj.append(341,341,341,341,341,341);
    obj.outTree();
    obj.deleteNodeByValue(-7,-7,-7,-7,-7,-7);
    obj.outTree();

    return 0;
}