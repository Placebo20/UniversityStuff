#include <iostream>
#include <vector>
#include <string>
#define COUNT 10
////////////////////////////////Tree////////////////////////////////////////

class Tree {
private:

	class Node{
	public:
	    int ID;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
		std::vector<Node*> leaves;
        Node(int year, int month, int day, int hour, int minute,int second);
	};
    int count;
	Node* root;
public:
	Tree(int year, int month, int day, int hour, int minute, int second);
	~Tree();
	Node* getRoot();
	void append(int year, int month, int day, int hour, int minute, int second);
	void setId(Node* current);
	void outputTree(Node* current, int temp = 0);
    void defaultOutput();
	Node* deleteNode();
	void deleteTree(Node* current);
	//Not completed
	void printNode(Node* current);
    void deleteNodeByIndex(int index);
    void deleteNodeByValue(int value);
    void searchNodeByValue(int value);
    Node* getParent(Node* current);
    void preOrder();

};

///////////////////////////////////////////////////////////////////////////////

//=============================BinaryTree====================================

class BinaryTree {
private:
    class Node {
    public:
        int id;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        Node* left;
        Node* right;
        Node(int year, int month, int day, int hour, int minute,int second);
    };
    Node* root;
    int count;
public:
    BinaryTree(int year, int month, int day, int hour, int minute,int second);
    ~BinaryTree();
    Node* getRoot();
    void setId(Node* current);
    void append(int year, int month, int day, int hour, int minute,int second);
    Node* deleteNode();
    void deleteTree();
    void output2dTreeUtil(Node* current, int space);
    void output2dTree(Node *current);
    void outTree();
    void printNode(Node* current);
    void print2DUtil(Node* current,int space);
    bool checkValues(Node *current, int year, int month, int day, int hour, int minute, int second);
    bool checkEqual(Node *current, int year, int month, int day, int hour, int minute, int second);
    bool check2Nodes(Node* current, Node* newNode);
    bool checkEqual(Node *current, Node *newNode);
    Node* getParent(Node* current, Node* tree);
    //Not completed
    void deleteNodeByValue(int year, int month, int day, int hour, int minute, int second);
    void deleteNodeByIndex(int index);
    void searchNodeByValue(int year, int month, int day, int hour, int minute, int second);
    void preOrder();

};

//===========================================================================

/////////////////////////////////BinarySearchTree////////////////////////////

class BinarySearchTree{
private:
    class Node{
    public:
        int id;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        Node* left;
        Node* right;
        Node(int year, int month, int day, int hour, int minute,int second);
    };
    Node* root;
    int count;
public:
    BinarySearchTree(int year, int month, int day, int hour, int minute,int second);
    ~BinarySearchTree();
    void setId(Node* current);
    bool checkValues(Node* current, int year, int month, int day, int hour, int minute,int second);
    bool checkEqual(Node *current, int year, int month, int day, int hour, int minute, int second);
    bool check2Nodes(Node* current, Node* newNode);
    bool checkEqual(Node* current, Node* newNode);
    void append(int year, int month, int day, int hour, int minute,int second);
    void output2dTreeUtil(Node* current, int space);
    void output2dTree(Node *current);
    void print2DUtil(Node* current,int space);
    void outTree();
    void printNode(Node* current);
    Node* deleteNode();
    void deleteTree();
    //Not completed
    void deleteNodeByValue(int year, int month, int day, int hour, int minute,int second);
    void deleteNodeByIndex(int index);
    void searchNodeByValue(int year, int month, int day, int hour, int minute,int second);
    Node* getParent(Node* tree,Node *current);
    void preOrder(Node* node);
};

///////////////////////////////////////////////////////////////////////////////