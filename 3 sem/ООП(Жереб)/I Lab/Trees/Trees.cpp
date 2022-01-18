#include "Trees.h"

//////////////////////////////////////Tree/////////////////////////////////////

Tree::Node::Node(int year, int month, int day, int hour, int minute, int second){
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

Tree::Tree(int year, int month, int day, int hour, int minute, int second) {
	root = new Node(year,month,day,hour,minute,second);
    count = 1;
    Tree::setId(root);
}

Tree::~Tree(){
	deleteTree(root);
}

Tree::Node* Tree::getRoot(){
	return root;
}

void Tree::outputTree(Node* current, int temp){
	std::cout << "[" << current->ID << "]:" << current << " : date = " << current->day << "/" << current->month << "/" << current->year << "year" << " " << current->hour << ":" << current->minute << ":" << current->second <<"\n";
	temp++;
	for(int i = 0; i < current->leaves.size(); i++){
		for(int j = 0; j < temp; j++)
			std::cout << '\t';
		std::cout << i << ". ";
		outputTree(current->leaves[i], temp);
	}
}

void Tree::defaultOutput() {
    outputTree(root,0);
}

void Tree::append(int year, int month, int day, int hour, int minute, int second){
	Node* current = root;	
	int tmp;
	if(root->leaves.empty()){
		Node* newNode = new Node(year,month,day,hour,minute,second);
        count++;
        Tree::setId(newNode);
		root->leaves.push_back(newNode);

		std::cout << "Tree is empty, node is added to root" << std::endl;
		return;
	}
	while(true) {
		Tree::outputTree(current);
	if(current->leaves.empty()){
		Node* newNode = new Node(year,month,day,hour,minute,second);
        count++;
        Tree::setId(newNode);
		current->leaves.push_back(newNode);
		return;
	}
	std::cout << "Free leaves: ";	
	for(int i = 0; i < current->leaves.size(); i++){
		std::cout << i << ' ';
	}
	std::cout << "\nChoose the leap or enter\"-1\"\n";
	std::cin >> tmp;
	if(tmp == -1){
		Node* newNode = new Node(year,month,day,hour,minute,second);
        count++;
        Tree::setId(newNode);
		current->leaves.push_back(newNode);
		return;
	} else 
		current = current->leaves[tmp];
	}	
}

Tree::Node* Tree::deleteNode() {
	Node* current = root;
	Node* previous = root;
	int tmp = -1, act;
	
	if(root->leaves.empty()) {
		std::cout << "There is no leaves..." << std::endl;
		return nullptr;
	}
	
	while (true) {
		Tree::outputTree(current);
		if(current->leaves.empty()){
			std::cout << "That node hasn't got leaves." << std::endl;
			previous->leaves.erase(previous->leaves.begin() + tmp);
			std::cout << "Node " << current << " is deleted" << std::endl;
			return current;
		}
		
		std::cout << "Free leaves: ";
		for(int i = 0; i < current->leaves.size(); i++)
			std::cout << i << ' ';
		std::cout << "\nChoose the leafe or press \"-1\"\n";
		std::cin >> act;
		if(act == -1){
			if(tmp == -1){
				std::cout << "You can't delete root" << std::endl;
				continue;
			}
			previous->leaves.erase(previous->leaves.begin() + tmp);
			std::cout << "Node " << current << " is deleted" << std::endl;
			return current;
			
		} else {
			tmp = act;
			previous = current;
			current = current->leaves[tmp];
		}
	}
}

void Tree::deleteTree(Tree::Node* current){
	for(auto & leaf : current->leaves)
		deleteTree(leaf);
	std::cout << "Node " << current << " is deleted" << std::endl;
	delete current;
}

void Tree::setId(Tree::Node *current) {
    current->ID = count;
}

void Tree::printNode(Tree::Node *current) {
    std::cout << "[" << current->ID << "]: " << current << " " <<
              current->day << "/" << current->month << "/" << current->year << "year" << " "
              << current->hour << ":" << current->minute << ":" << current->second;
}

//Not completed
void Tree::searchNodeByValue(int value) {

}
void Tree::deleteNodeByIndex(int index) {
    Node *current = root;
    for (int i = 0; i < current->leaves.size(); i++) {
        if (current->leaves[i]->ID == index) {
            std::cout << "Node " << current->leaves[i] <<  " is deleted."
                      << std::endl;
            current = current->leaves[i];
            while (true) {
                if (current->leaves.size() == 0) {
                    current = nullptr;
                    return;
                } else {
                    for (int i = 0; i < current->leaves.size(); i++) {
                        current->leaves[i] = nullptr;
                    }
                }
            }
        }
    }
}
void Tree::deleteNodeByValue(int value){
}
void Tree::preOrder() {

}
Tree::Node* Tree::getParent(Node* current) {
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////BinaryTree/////////////////////////////////////////////

BinaryTree::Node::Node(int year, int month, int day, int hour, int minute,int second) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    left = right = nullptr;
}

BinaryTree::~BinaryTree() {
    print2DUtil(root, 0);
    deleteTree();
}

BinaryTree::BinaryTree(int year, int month, int day, int hour, int minute,int second) {
    root = new Node(year,month,day,hour,minute,second);
    count++;
    setId(root);
    std::cout << "Root " << root << " is created." << std::endl;
}

BinaryTree::Node* BinaryTree::getRoot() {
    return root;
}

void BinaryTree::setId(Node *current) {
    current->id = count;
}

void BinaryTree::append(int year, int month, int day, int hour, int minute,int second) {
    Node *current = root;
    int tmp;
    while (true) {
        if ((current->left != nullptr) && (current->right != nullptr)) {
            std::cout << "Choose the Node we need to go" << std::endl;
            std::cout << "[1]Left: " << current->left << "\t" << "[2]Right: " << current->right << std::endl;
            std::cin >> tmp;
            switch (tmp) {
                case 1:
                    current = current->left;
                    break;
                case 2:
                    current = current->right;
                    break;
                default:
                    std::cout << "Not integer expression." << std::endl;
            }
        } else {
            if ((current->left == nullptr) && (current->right != nullptr)) {
                std::cout << "Choose the Node we need to go" << std::endl;
                std::cout << "[1]Left(Creating): " << current->left << "\t" << "[2]Right: " << current->right
                          << std::endl;
                std::cin >> tmp;
                switch (tmp) {
                    case 1:
                        current->left = new Node(year,month,day,hour,minute,second);
                        count++;
                        setId(current->left);
                        return;
                    case 2:
                        current = current->right;
                        break;
                    default:
                        break;
                }

            } else if ((current->left != nullptr) && (current->right == nullptr)) {
                std::cout << "Choose the Node we need to go" << std::endl;
                std::cout << "[1]Left: " << current->left << "\t" << "[2]Right(Creating): " << current->right
                          << std::endl;
                std::cin >> tmp;
                switch (tmp) {
                    case 1:
                        current = current->left;
                        break;
                    case 2:
                        current->right = new Node(year,month,day,hour,minute,second);
                        count++;
                        setId(current->right);
                        return;
                    default:
                        break;
                }
            } else {
                std::cout << "Choose the Node we need to go" << std::endl;
                std::cout << "[1]Left(Creating): " << current->left << "\t" << "[2]Right(Creating): " << current->right
                          << std::endl;
                std::cin >> tmp;
                switch (tmp) {
                    case 1:
                        current->left = new Node(year,month,day,hour,minute,second);
                        count++;
                        setId(current->left);
                        return;
                    case 2:
                        current->right = new Node(year,month,day,hour,minute,second);
                        count++;
                        setId(current->right);
                        return;
                    default:
                        break;
                };
            }
        }
    }
}

BinaryTree::Node* BinaryTree::deleteNode()
{
    Node* previous = root;
    Node* current = root;
    if ((root->left == nullptr) && (root->right == nullptr)){ //Если потомки корня == nullptr, затираем указатель на корень
        std::cout << "Root hasn't got leaves" << std::endl;
        root = nullptr;
        std::cout << "Tree with root "<< current <<" is deleted." << std::endl;
        return nullptr;
    }
    while (true) { // Проход по дереву и затирание указателей
        if (current->left != nullptr) {
            previous = current;
            current = current->left;
        } else if ((current->left == nullptr) && (current->right != nullptr)) {
            previous = current;
            current = current->right;
        } else {
            std::cout << "Node " << current << " is deleted." << std::endl;
            if(previous->left == current)
                previous->left = nullptr;
            else
                previous->right = nullptr;
            current = nullptr;
            return nullptr;
        }
    }
}

void BinaryTree::deleteTree(){
    while(root != nullptr)
        deleteNode();
}

void BinaryTree::output2dTreeUtil(Node* current, int space){
    if (root == nullptr)
        return;
    space += COUNT;
    output2dTreeUtil(root->right, space);
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<<root->day << "/" << root->month << "/" << root->year << "year" << " " << root->hour << ":" << root->minute << ":" << root->second <<"\n";
    output2dTreeUtil(root->left, space);
}

void BinaryTree::output2dTree(Node *current){
    output2dTreeUtil(current, 0);
}

void BinaryTree::print2DUtil(Node* current, int space)
{
    if (current == nullptr)
        return;

    space += COUNT;

    print2DUtil(current->right, space);

    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<<current->day << "/" << current->month << "/" << current->year << "year" << " " << current->hour << ":" << current->minute << ":" << current->second <<"\n";

    print2DUtil(current->left, space);
}

void BinaryTree::outTree() {
    print2DUtil(root,0);
}

void BinaryTree::printNode(BinaryTree::Node *current) {
    std::cout << "[" << current->id << "]: " << current << " " <<
              current->day << "/" << current->month << "/" << current->year << "year" << " "
              << current->hour << ":" << current->minute << ":" << current->second;
}

bool BinaryTree::checkValues(Node *current, int year, int month, int day, int hour, int minute, int second) {
    if(current->year >= year){
        if(current->month >= month){
            if(current->day >= day){
                if(current->hour >= hour) {
                    if (current->minute >= minute) {
                        if (current->second > second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool BinaryTree::checkEqual(Node *current, int year, int month, int day, int hour, int minute, int second){
    if(current->year == year){
        if(current->month == month){
            if(current->day == day){
                if(current->hour == hour) {
                    if (current->minute == minute) {
                        if (current->second == second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool BinaryTree::check2Nodes(Node* current, Node* newNode){
    if(current->year <= newNode->year){
        if(current->month <= newNode->month){
            if(current->day <= newNode->day){
                if(current->hour <= newNode->hour) {
                    if (current->minute <= newNode->minute) {
                        if (current->second < newNode->second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool BinaryTree::checkEqual(Node *current, Node *newNode) {
    if(current->year == newNode->year){
        if(current->month == newNode->month){
            if(current->day == newNode->day){
                if(current->hour == newNode->hour) {
                    if (current->minute == newNode->minute) {
                        if (current->second == newNode->second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

BinaryTree::Node* BinaryTree::getParent(Node* tree,Node *current) { // Node* parent = getParent(current);
    if(!checkEqual(current, tree)) {
        if (check2Nodes(current, tree)) { //Если дата current меньше чем tree
            Node *res = getParent(tree->left, current); //Получаем родителя для tree->left, рекурсивный проходи
            if (res)
                return res;
            return tree;
        } else if (!check2Nodes(current, tree)) {
            Node *res = getParent(tree->right, current);
            if (res)
                return res;
            return tree;
        }
    } else return nullptr;
}

//Not complete
void BinaryTree::searchNodeByValue(int year, int month, int day, int hour, int minute, int second) {
    Node* current = root;
    Node* previous = root;
    while(true){
        // if(current->data == value)
        //     std::cout<<"Node " << current << " has value = " << current->data << std::endl;
    }
}
void BinaryTree::deleteNodeByValue(int year, int month, int day, int hour, int minute, int second) {
    Node* current = root;
    Node* parent = getParent(root, current);
    if(current->left == nullptr && current->right == nullptr){
        if(checkEqual(current,year,month,day,hour,minute,second)){
            if(parent->left == current)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        } else return;
    } else if(current->left == nullptr || current->right == nullptr) {
        if (checkEqual(current, year, month, day, hour, minute, second)) {
            if (current->left == nullptr) {
                if (parent->left = current) {
                    parent->left = current->left;
                    current = parent->left;
                } else {
                    parent->right = current->left;
                    current = parent->right;
                }
            } else {
                if (parent->left = current) {
                    parent->left = current->right;
                    current = parent->left;
                } else {
                    parent->right = current->right;
                    current = parent->right;
                }
            }
        } else {

        }
    }
}
void BinaryTree::deleteNodeByIndex(int index) {

}
void BinaryTree::preOrder() {

}

//////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////BinarySearchTree//////////////////////////////////////////

BinarySearchTree::Node::Node(int year, int month, int day, int hour, int minute,int second) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    left = right = nullptr;
}

BinarySearchTree::BinarySearchTree(int year, int month, int day, int hour, int minute,int second){
    count = 1;
    root = new Node(year,month,day,hour,minute,second);
    std::cout << "Root " << root << " is created." << std::endl;
}

void BinarySearchTree::setId(Node *current) {
    current->id = count;
}

BinarySearchTree::~BinarySearchTree() {
    deleteTree();
}

void BinarySearchTree::output2dTreeUtil(Node* current, int space){
    if (root == nullptr)
        return;
    space += COUNT;
    output2dTreeUtil(root->right, space);
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<<root->day << "/" << root->month << "/" << root->year << "year" << " " << root->hour << ":" << root->minute << ":" << root->second <<"\n";
    output2dTreeUtil(root->left, space);
}

void BinarySearchTree::output2dTree(Node *current){
    output2dTreeUtil(current, 0);
}

void BinarySearchTree::print2DUtil(Node* current, int space)
{
    if (current == nullptr)
        return;

    space += COUNT;

    print2DUtil(current->right, space);

    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<< current->day << "/" << current->month << "/" << current->year << "year" << " " << current->hour << ":" << current->minute << ":" << current->second <<"\n";

    print2DUtil(current->left, space);
}

void BinarySearchTree::printNode(Node *current) {
    std::cout << "[" << current->id << "]: " << current << " " <<
    current->day << "/" << current->month << "/" << current->year << "year" << " "
    << current->hour << ":" << current->minute << ":" << current->second;
}

bool BinarySearchTree::checkValues(Node *current, int year, int month, int day, int hour, int minute, int second) {
    if(current->year >= year){
        if(current->month >= month){
            if(current->day >= day){
                if(current->hour >= hour) {
                    if (current->minute >= minute) {
                        if (current->second > second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool BinarySearchTree::checkEqual(Node *current, int year, int month, int day, int hour, int minute, int second){
    if(current->year == year){
        if(current->month == month){
            if(current->day == day){
                if(current->hour == hour) {
                    if (current->minute == minute) {
                        if (current->second == second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool BinarySearchTree::check2Nodes(Node* current, Node* newNode){
    if(current->year <= newNode->year){
        if(current->month <= newNode->month){
            if(current->day <= newNode->day){
                if(current->hour <= newNode->hour) {
                    if (current->minute <= newNode->minute) {
                        if (current->second < newNode->second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool BinarySearchTree::checkEqual(Node *current, Node *newNode) {
    if(current->year == newNode->year){
        if(current->month == newNode->month){
            if(current->day == newNode->day){
                if(current->hour == newNode->hour) {
                    if (current->minute == newNode->minute) {
                        if (current->second == newNode->second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

void BinarySearchTree::append(int year, int month, int day, int hour, int minute, int second){
    Node* current = root;
    while(true){
        if(checkValues(current,year,month,day,hour,minute,second)) {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                count++;
                current->left = new Node(year,month,day,hour,minute,second);
                setId(current->left);
                return;
            }
        } else {
            if (current->right != nullptr) {
                current = current->right;

            } else {
                count++;
                current->right = new Node(year, month, day, hour, minute, second);
                setId(current->right);
                return;
            }
        }
    }
}

void BinarySearchTree::searchNodeByValue(int year, int month, int day, int hour, int minute,int second) {
    Node* current = root;
    while(true){
        if(checkValues(current,year,month,day,hour,minute,second)){
            if(checkEqual(current,year,month,day,hour,minute,second)){
                std::cout << "Node "; printNode(current); std::cout << " searched!" << std::endl;
            } else
                if(current->left != nullptr)
                    current = current->left;
                else{
                    std::cout << "Can't search nothing more." << std::endl;
                    return;
                }
        } else {
            if(current->right != nullptr)
                current = current->right;
            else{
                std::cout << "Can't search nothing more." << std::endl;
                return;
            }
        }
    }
}

BinarySearchTree::Node* BinarySearchTree::deleteNode() {
    Node* previous = root;
    Node* current = root;
    if ((root->left == nullptr) && (root->right == nullptr)){ //Если потомки корня == nullptr, затираем указатель на корень
        std::cout << "Root hasn't got leaves" << std::endl;
        root = nullptr;
        std::cout << "Tree with root "<< current <<" is deleted." << std::endl;
        return nullptr;
    }
    while (true) { // Проход по дереву и затирание указателей
        if (((current->left != nullptr) && (current->right == nullptr)) ||
            ((current->left != nullptr) && (current->right != nullptr))) {
            previous = current;
            current = current->left;
        } else if ((current->left == nullptr) && (current->right != nullptr)) {
            previous = current;
            current = current->right;
        } else {
            std::cout << "Node " << current << " is deleted." << std::endl;
            if(previous->left == current)
                previous->left = nullptr;
            else
                previous->right = nullptr;
            current = nullptr;
            return nullptr;
        }
    }
}

void BinarySearchTree::deleteTree() {
    while(root != nullptr)
        deleteNode();
}

void BinarySearchTree::outTree() {
    std::cout << "======================================================" << std::endl;
    print2DUtil(root,0);
    std::cout << "======================================================" << std::endl;
}

void BinarySearchTree::deleteNodeByValue(int year, int month, int day, int hour, int minute, int second) {
    Node *current = root;
    Node *parent = getParent(root, current);

    if (current->left == nullptr && current->right == nullptr) { // Если потомки отсутствуют
        if (!checkEqual(current, year, month, day, hour, minute, second))
            return;
        else {
            if (parent->left == current) {
                parent->left = nullptr;
                return;
            } else if (parent->right == current) {
                parent->right = nullptr;
                return;
            }
        }
    } else if (current->left == nullptr || current->right == nullptr) { // 1 потомок
        if (checkEqual(current, year, month, day, hour, minute, second)) {
            if (current->left == nullptr) {
                if (parent->left == nullptr)
                    parent->left = current->right;
                else
                    parent->right = current->right;
            } else {
                if (parent->left == current)
                    parent->left = current->left;
                else
                    parent->right = current->left;
            }
        } else {
            if (current->left == nullptr) {
                if (!checkValues(current, year, month, day, hour, minute, second))
                    current = current->right;
                else return;
            } else if (current->right == nullptr) {
                if (checkValues(current, year, month, day, hour, minute, second))
                    current = current->left;
                else return;
            }
        }
    } else { // 2 потомка
        while (true) {
            parent = getParent(root, current);
            Node* temp = current->left;
            if(parent != nullptr) {
                if ((current->left == nullptr && current->right == nullptr) && !checkEqual(current, year, month, day, hour, minute, second))
                    return;
                else if (checkEqual(current, year, month, day, hour, minute, second)) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                    while (temp->right)
                        temp = temp->right;
                    temp->right = current->right;
                    current = temp;
                } else if (!checkEqual(current, year, month, day, hour, minute, second)) {
                    if (current->left != nullptr && current->right != nullptr) {
                        if (checkValues(current, year, month, day, hour, minute, second))
                            current = current->right;
                        else current = current->left;
                    } else if (current->left != nullptr) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }
            } else {
                if (!checkEqual(current, year, month, day, hour, minute, second)) {
                    if (checkValues(current, year, month, day, hour, minute, second) && current->left != nullptr)
                        current = current->left;
                    else if(!checkValues(current, year, month, day, hour, minute, second) && current->right != nullptr)
                        current = current->right;
                }
            }
        }
    }
}

BinarySearchTree::Node* BinarySearchTree::getParent(Node* tree,Node *current) { // Node* parent = getParent(current);
    if(!checkEqual(current, tree)) {
        if (check2Nodes(current, tree)) { //Если дата current меньше чем tree
            Node *res = getParent(tree->left, current); //Получаем родителя для tree->left, рекурсивный проходи
            if (res)
                return res;
            return tree;
        } else if (!check2Nodes(current, tree)) {
            Node *res = getParent(tree->right, current);
            if (res)
                return res;
            return tree;
        }
    } else return nullptr;
}

//Not complete

void BinarySearchTree::deleteNodeByIndex(int index) {

}

void BinarySearchTree::preOrder(Node *node) {
    if(node == nullptr)
        return;
    preOrder(node->left);
    preOrder(node->right);
    
}


/////////////////////////////////////////////////////////////////////////////////////////
