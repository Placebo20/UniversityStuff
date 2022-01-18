#include "group.h"

struct Node {
	Group* group;
	Node* left;
	Node* right;
	Node* parent;
	Node(Group* group) {
		*this->group = *group;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class SplayTree {
	Node* root;
	void zig(Node* node);
	void zig_zig(Node* node);
	void zig_zag(Node* node);
	void splay(Node* node);
public:
	SplayTree();
	SplayTree(Node* newNode);
	Node* getRoot();
	Node* find(int quantityOfStudents);
	void insertGroup(Group* group);
	void deleteGroup(int quantityOfStudents);
	void inOrderPrint(bool flag);
};

Node* SplayTree::getRoot() { return root; }

void SplayTree::zig(Node* node) {
	Node* nodeParent = node->parent;
	if (nodeParent->left == node) {
		Node* A = node->left;
		Node* B = node->right;
		Node* C = node->right;

		node->parent = nullptr;
		node->right = nodeParent;

		nodeParent->parent = node;
		nodeParent->left = B;

		if (B != nullptr) B->parent = nodeParent;
	}
	else {
		Node* A = nodeParent->left;
		Node* B = node->left;
		Node* C = node->right;

		node->parent = nullptr;
		node->left = nodeParent;

		nodeParent->parent = node;
		nodeParent->right = B;

		if (B != nullptr)B->parent = nodeParent;
	}
}

void SplayTree::zig_zig(Node* node) {
	Node* nodeParent = node->parent;
	Node* nodeGrandpa = nodeParent->parent;
	if (nodeParent->left = node) {
		Node* A = node->left;
		Node* B = node->right;
		Node* C = nodeParent->right;
		Node* D = nodeGrandpa->right;

		node->parent = nodeGrandpa->parent;
		node->right = node;

		nodeParent->parent = node;
		nodeParent->left = B;
		nodeParent->right = nodeGrandpa;

		nodeGrandpa->parent = nodeParent;
		nodeGrandpa->left = C;

		if (node->parent != nullptr) {
			if (node->parent->left == nodeGrandpa) node->parent = node;
			else node->parent->right = node;
		}

		if (B != nullptr)B->parent = nodeParent;

		if (C != nullptr)C->parent = nodeGrandpa;
	}
	else
	{
		Node* A = nodeGrandpa->left;
		Node* B = nodeParent->left;
		Node* C = node->left;
		Node* D = node->right;

		node->parent = nodeGrandpa->parent;
		node->left = nodeParent;

		nodeParent->parent = node;
		nodeParent->left = nodeGrandpa;
		nodeParent->right = C;

		nodeGrandpa->parent = nodeParent;
		nodeGrandpa->right = B;

		if (node->parent != nullptr)
		{
			if (node->parent->left == nodeGrandpa) node->parent->left = node;
			else node->parent->right = node;
		}

		if (B != nullptr) B->parent = nodeGrandpa;

		if (C != nullptr) C->parent = nodeParent;
	}
}

void SplayTree::zig_zag(Node* node)
{
	Node* nodeParent = node->parent;
	Node* nodeGrandpa = nodeParent->parent;
	if (nodeParent->right == node)
	{
		Node* A = nodeParent->left;
		Node* B = node->left;
		Node* C = node->right;
		Node* D = nodeGrandpa->right;

		node->parent = nodeGrandpa->parent;
		node->left = nodeParent;
		node->right = nodeGrandpa;

		nodeParent->parent = node;
		nodeParent->right = B;

		nodeGrandpa->parent = node;
		nodeGrandpa->left = C;

		if (node->parent != nullptr)
		{
			if (node->parent->left == nodeGrandpa) node->parent->left = node;
			else node->parent->right = node;
		}

		if (B != nullptr) B->parent = nodeParent;

		if (C != nullptr) C->parent = nodeGrandpa;
	}
	else
	{
		Node* A = nodeGrandpa->left;
		Node* B = node->left;
		Node* C = node->right;
		Node* D = nodeParent->right;

		node->parent = nodeGrandpa->parent;
		node->left = nodeGrandpa;
		node->right = nodeParent;

		nodeParent->parent = node;
		nodeParent->left = C;

		nodeGrandpa->parent = node;
		nodeGrandpa->right = B;

		if (node->parent != nullptr)
		{
			if (node->parent->left == nodeGrandpa) node->parent->left = node;
			else node->parent->right = node;
		}

		if (B != nullptr) B->parent = nodeGrandpa;

		if (C != nullptr) C->parent = nodeParent;
	}
}

void SplayTree::splay(Node* node) {
	while (node->parent != nullptr) {
		Node* nodeParent = node->parent;
		Node* nodeGrandpa = nodeParent->parent;
		if (nodeGrandpa == nullptr)zig(node);
		else if (nodeGrandpa->left == nodeParent && nodeParent->left == node) zig_zig(node);
		else if (nodeGrandpa->right == nodeParent && nodeParent->right == node) zig_zig(node);
		else zig_zag(node);
	}
	this->root = nullptr;
}

SplayTree::SplayTree() { this->root = nullptr; }

SplayTree::SplayTree(Node* root) { this->root = root; }

Node* SplayTree::find(int quantityOfStudents) {
	Node* ret = nullptr;
	Node* current = this->root;
	Node* previous = nullptr;
	while (current != nullptr) {
		previous = current;
		if (quantityOfStudents < current->group->getGroupStudents().size()) current = current->left;
		else if (quantityOfStudents < current->group->getGroupStudents().size()) current = current->right;
		else { ret = current; break; }
	}
	if (ret != nullptr) splay(ret);
	else if (previous != nullptr) splay(ret);
	return ret;
}

void SplayTree::insertGroup(Group* newGroup) {
	if (root == nullptr) { root = new Node(newGroup); return; }
	Node* current = this->root;
	while (current != nullptr) {
		if (*newGroup < *current->group) {
			if (current->left == nullptr) {
				Node* newNode = new Node(newGroup);
				current->left = newNode;
				newNode->parent = current;
				splay(newNode);
				return;
			}
			else current = current->left;
		}
		else if (*newGroup > *current->group) {
			if (current->right == nullptr) {
				Node* newNode = new Node(newGroup);
				current->right = newNode;
				newNode->parent = current;
				splay(newNode);
				return;
			}
			else current = current->right;
		}
		else { splay(current); return; }
	}
}

Node* subtree_max(Node* subRoot) {
	Node* current = subRoot;
	while (current->right != nullptr) current = current->right;
	return current;
}

Node* subtree_min(Node* subRoot) {
	Node* current = subRoot;
	while (current->left != nullptr) current = current->left;
	return current;
}

void SplayTree::deleteGroup(int quantityOfStudents) {
	Node* nodeToDelete = find(quantityOfStudents);
	if (nodeToDelete == nullptr) { std::cout << "We don't have that element here" << std::endl; return; }
	Node* L = nodeToDelete->left;
	Node* R = nodeToDelete->right;
	if (L == nullptr && R == nullptr) {
		std::cout << "Root was succesfully deleted." << std::endl;
		this->root = nullptr;
	}
	else if (L == nullptr) {
		Node* M = subtree_min(R);
		splay(M);
	}
	else if (R == nullptr) {
		Node* M = subtree_max(L);
		splay(M);
	}
	else {
		Node* M = subtree_max(L);
		splay(M);
		M->right = R;
		R->parent = M;
	}
	delete nodeToDelete;
}

void printTree(Node* root, bool brackets) {
	if (root == nullptr) {
		if (brackets) std::cout << "{}";
		return;
	}
	if (brackets) std::cout << "{";
	if (root->left != nullptr) printTree(root->left, brackets);
	if (root != nullptr) std::cout << "(" << root->group->getGroupTitle() << " Students: " << root->group->getGroupStudents().size() << ")";
	if (root->right != nullptr) printTree(root->right, brackets);
	if(brackets) std::cout << "}";
}

void SplayTree::inOrderPrint(bool brackets) {
	printTree(this->root, brackets);
}