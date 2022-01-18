#include "group.h"
#include <list>

struct Node{
	Group* group;
	Node* parent;
	Node* left;
	Node* right;
	char color;
};

class RBTree {
	Node* root;
public:
	RBTree() : root(nullptr) {}

	Node* getRoot() { return root; }
	Node* treeSearch(std::string titleToSearch, Node* temp) {
		
		if (temp == nullptr) { return nullptr; }
		while (temp) {
			if (titleToSearch == temp->group->getGroupTitle()) {
				std::cout << "We found this Node! Is: " << temp << std::endl;
				std::cout << "Students: ";
				printStudents(temp->group);
				return temp; 
			}
			treeSearch(titleToSearch, temp->left);
			treeSearch(titleToSearch, temp->right);
		}
		std::cout << "That group doesn't exist!" << std::endl;
		return nullptr;
	}

	void printStudents(Group* groupToPrint) {
		for (unsigned int i = 0; i < groupToPrint->getGroupStudents().size(); i++) {
			std::cout << "[" << i << "]: " << groupToPrint->getGroupStudents().at(i)->getName() << std::endl;
		}
	}
	void insert(Group* newGroup) {
		if (root == nullptr) {
			root = new Node();
			root->group = newGroup;
			root->parent = nullptr;
			root->color = 'B';
			std::cout << "Element inserted. Root is created!" << std::endl;
		}
		else {
			Node* linker = getRoot();
			Node* newNode = new Node();
			newNode->group->setGroupTitle(newGroup->getGroupTitle());
			//Может быть здесь не правильно написано
			newNode->group->setGroupStudents(newGroup->getGroupStudents());
			//

			while (linker != nullptr) {
				if (linker->group->getGroupStudents().size() > newGroup->getGroupStudents().size()) {
					if (linker->left == nullptr) {
						linker->left = newNode;
						newNode->color = 'R';
						newNode->parent = linker;
						std::cout << "Element inserted." << std::endl;
						break;
					}
					else {
						linker = linker->left;
					}
				}
				else {
					if (linker->right == nullptr) {
						linker->right = newNode;
						newNode->color = 'R';
						newNode->parent = linker;
						std::cout << "Element inserted" << std::endl;
					}
					else {
						linker = linker->right;
					}
				}
			}
			repaintingInsert(newNode);
		}
	}
	void repaintingInsert(Node* nodeToRepaint) {
		while (nodeToRepaint->parent->color == 'R') {
			Node* grandpa = nodeToRepaint->parent->parent;
			Node* uncle = getRoot();
			if (nodeToRepaint->parent == grandpa->left) {
				if (grandpa->right) {
					uncle = grandpa->left;
				}
				if (uncle->color == 'R') {
					nodeToRepaint->parent->color = 'B';
					uncle->color = 'B';
					grandpa->color = 'R';
					if (grandpa->group->getGroupStudents().size() != root->group->getGroupStudents().size()) {
						nodeToRepaint = grandpa;
					}
					else { break; }
				}
				else if (nodeToRepaint == grandpa->left->right) {
					leftRotate(nodeToRepaint->parent);
				}
				else {
					nodeToRepaint->parent->color = 'B';
					grandpa->color = 'R';
					rightRotate(grandpa);
					if (*grandpa->group != *root->group) {
						nodeToRepaint = grandpa;
					}
					else { break; }
				}
			}
			else {
				if (grandpa->left) {
					uncle = grandpa->left;
				}
				if (uncle->color == 'R') {
					nodeToRepaint->parent->color = 'B';
					uncle->color = 'B';
					grandpa->color = 'R';
					if (*grandpa->group != *root->group) {
						nodeToRepaint = grandpa;
					}
					else { break; }
				}
				else if (nodeToRepaint == grandpa->right->left) {
					rightRotate(nodeToRepaint->parent);
				}
				else {
					nodeToRepaint->parent->color = 'B';
					grandpa->color = 'R';
					leftRotate(grandpa);
					if (*grandpa->group != *root->group)
					{
						nodeToRepaint = grandpa;
					}
					else {
						break;
					}
				}
			}
		}
		root->color = 'B';
	}

	void leftRotate(Node* nodeToRotate) {
		Node* rNode = new Node();
		if (nodeToRotate->right->left) {
			rNode->right = nodeToRotate->right->left;
		}
		rNode->left = nodeToRotate->left;
		rNode->group->setGroupTitle(nodeToRotate->group->getGroupTitle());
		rNode->group->setGroupStudents(nodeToRotate->group->getGroupStudents());
		rNode->color = nodeToRotate->color;
		nodeToRotate->group->setGroupTitle(nodeToRotate->right->group->getGroupTitle());
		nodeToRotate->group->setGroupStudents(nodeToRotate->right->group->getGroupStudents());

		nodeToRotate->left = rNode;
		if (rNode->left) {
			rNode->left->parent = rNode;
		}
		if (rNode->right) {
			rNode->right->parent = rNode;
		}
		rNode->parent = nodeToRotate;

		if (nodeToRotate->right->right) {
			nodeToRotate->right = nodeToRotate->right->right;
		}
		else {
			nodeToRotate->right = nullptr;
		}
		if (nodeToRotate->right) { nodeToRotate->right->parent = nodeToRotate; }
	}
	void rightRotate(Node* nodeToRotate) {
		Node* rNode = new Node();
		if (nodeToRotate->left->right) {
			rNode->left = nodeToRotate->left->right;
		}
		rNode->right = nodeToRotate->right;
		rNode->group->setGroupTitle(nodeToRotate->group->getGroupTitle());
		rNode->group->setGroupStudents(nodeToRotate->group->getGroupStudents());
		rNode->color = nodeToRotate->color;
		nodeToRotate->group->setGroupTitle(nodeToRotate->left->group->getGroupTitle());
		//Возможно тут ошибка
		nodeToRotate->group->setGroupStudents(nodeToRotate->left->group->getGroupStudents());

		nodeToRotate->right = rNode;
		if (rNode->left) {
			rNode->left->parent = rNode;
		}
		if (rNode->right) {
			rNode->right->parent = rNode;
		}
		rNode->parent = nodeToRotate;

		if (nodeToRotate->left->left) {
			nodeToRotate->left = nodeToRotate->left->left;
		}
		else {
			nodeToRotate->left = nullptr;
		}
		if (nodeToRotate->left) { nodeToRotate->left->parent = nodeToRotate; }
	}

	void removeNode(Node* parent, Node* current, Group* groupToRemove) {
		if (current == nullptr) { std::cout << "Are you ok?" << std::endl; return; }
		if (current->group->getGroupStudents().size() == groupToRemove->getGroupStudents().size()) {
			//Case-1
			if (current->left == nullptr && current->right == nullptr) {
				if (parent != nullptr) {
					if (parent->group->getGroupStudents().size() == current->group->getGroupStudents().size()) {
						root = nullptr;
					}
					else if (parent->right == current) {
						repaintingRemove(current);
						parent->right = nullptr;
					}
					else {
						repaintingRemove(current);
						parent->left = nullptr;
					}
				}
				else { root = nullptr; }
			}
			//Case-2
			else if (current->left != nullptr && current->right == nullptr) {
				Group* swap = new Group();
				swap->setGroupTitle(current->group->getGroupTitle());
				swap->setGroupStudents(current->group->getGroupStudents());
				current->group->setGroupStudents(current->left->group->getGroupStudents());
				current->group->setGroupTitle(current->left->group->getGroupTitle());
				current->left->group->setGroupStudents(swap->getGroupStudents());
				current->left->group->setGroupTitle(swap->getGroupTitle());
				removeNode(current, current->right, groupToRemove);
			}
			else if (current->left == nullptr && current->right != nullptr) {
				Group* swap = new Group();
				swap->setGroupTitle(current->group->getGroupTitle());
				swap->setGroupStudents(current->group->getGroupStudents());
				current->group->setGroupStudents(current->right->group->getGroupStudents());
				current->group->setGroupTitle(current->right->group->getGroupTitle());
				current->right->group->setGroupStudents(swap->getGroupStudents());
				current->right->group->setGroupTitle(swap->getGroupTitle());
				removeNode(current, current->right, groupToRemove);
			}
			else {
				bool flag = false;
				Node* tmp = current->right;
				while (tmp->left) { flag = true; parent = tmp; tmp = tmp->left; }
				if (!flag) { parent = current; }
				Group* swap = new Group();
				swap->setGroupTitle(current->group->getGroupTitle());
				swap->setGroupStudents(current->group->getGroupStudents());
				current->group->setGroupStudents(tmp->group->getGroupStudents());
				current->group->setGroupTitle(tmp->group->getGroupTitle());
				tmp->group->setGroupStudents(swap->getGroupStudents());
				tmp->group->setGroupTitle(swap->getGroupTitle());
				removeNode(parent, tmp, swap);
			}
		}
		std::cout << "Group(Node) was succesfully removed." << std::endl;
	}
	void remove(std::string titleToDelete, Node* temp){

		if (temp == nullptr) { 
			std::cout << "Tree is empty!";
			return; 
		}
		while (temp) {
			if (titleToDelete == temp->group->getGroupTitle()) {
				removeNode(temp->parent, temp, temp->group);
			}
			treeSearch(titleToDelete, temp->left);
			treeSearch(titleToDelete , temp->right);
		}
		std::cout << "That group doesn't exist!" << std::endl;
		return;
	}
	void repaintingRemove(Node* nodeToRepaint) {
		while (*nodeToRepaint->group != *root->group && nodeToRepaint->color == 'B') {
			Node* sibling = getRoot();
			if (nodeToRepaint->parent->left == nodeToRepaint) {
				if (nodeToRepaint->parent->right) { sibling = nodeToRepaint->parent->right; }
				if (sibling) {
					//Case-1
					if (sibling->color == 'R') {
						sibling->color = 'B';
						nodeToRepaint->parent->color = 'R';
						leftRotate(nodeToRepaint->parent);
						sibling = nodeToRepaint->parent->right;
					}
					//Case-2
					if (sibling->left == nullptr && sibling->right == nullptr) {
						sibling->color = 'R';
						nodeToRepaint = nodeToRepaint->parent;
					}
					else if (sibling->left->color == 'B' && sibling->right->color == 'B') {
						sibling->color = 'R';
						nodeToRepaint = nodeToRepaint->parent;
					}
					//Case-3
					else if (sibling->right->color == 'B') {
						sibling->left->color = 'B';
						sibling->color = 'R';
						rightRotate(sibling);
						sibling = nodeToRepaint->parent->right;
					}
					else {
						sibling->color = nodeToRepaint->parent->color;
						nodeToRepaint->parent->color = 'B';
						if (sibling->right) { sibling->right->color = 'B'; }
						leftRotate(nodeToRepaint->parent);
						nodeToRepaint = root;
					}
				}
			}
			else {
				if (nodeToRepaint->parent->right == nodeToRepaint) {
					if (nodeToRepaint->parent->left) { sibling = nodeToRepaint->parent->left; }
					if (sibling) {
						//Case-1
						if (sibling->color == 'R') {
							sibling->color = 'B';
							nodeToRepaint->parent->color = 'R';
							rightRotate(nodeToRepaint->parent);
							sibling = nodeToRepaint->parent->left;
						}
						//Case-2
						if (sibling->left == nullptr && sibling->right == nullptr) {
							sibling->color = 'R';
							nodeToRepaint = nodeToRepaint->parent;
						}
						else if(sibling->left->color == 'B' && sibling->right->color == 'B') {
							sibling->color = 'R';
							nodeToRepaint = nodeToRepaint->parent;
						}
						//Case-3
						else if (sibling->left->color == 'B') {
							sibling->right->color = 'B';
							sibling->color = 'R';
							rightRotate(sibling);
							sibling = nodeToRepaint->parent->left;
						}
						else {
							sibling->color = nodeToRepaint->parent->color;
							nodeToRepaint->parent->color = 'B';
							if (sibling->left) { sibling->left->color = 'B'; }
							leftRotate(nodeToRepaint->parent);
							nodeToRepaint = root;
						}
					}
				}
			}
		}
		nodeToRepaint->color = 'B';
	}

	void preorderWalk(Node* temp) {
		if (!temp) { return; }
		std::cout << "--> " << "(" << temp->group->getGroupTitle() << " Students:" << temp->group->getGroupStudents().size() << ")";
		preorderWalk(temp->left);
		preorderWalk(temp->right);
	}
	void postorderWalk(Node* temp) {
		if (!temp) { return; }
		std::cout << "--> " << "(" << temp->group->getGroupTitle() << " Students:" << temp->group->getGroupStudents().size() << ")"<<"<"<<temp->color<<">";
		preorderWalk(temp->left);
		preorderWalk(temp->right);
		std::cout << "--> " << "(" << temp->group->getGroupTitle() << " Students:" << temp->group->getGroupStudents().size() << ")"<<"<"<<temp->color<<">";
	}
};

/*Node* temp = root;
		Node* parent = temp;
		bool flag = false;
		if (!temp) { removeNode(nullptr, nullptr, temp->group); }
		while (temp) {
			if (titleToDelete == temp->group->getGroupTitle) {
				flag = true;
				removeNode(parent, temp, temp->group);
			}
			else if (*groupToRemove < *temp->group) { parent = temp; temp = temp->left; }
			else { parent = temp; temp = temp->right; }
		}
		if (!flag) { std::cout << "\nGroup doesn't exist in the table"; }*/