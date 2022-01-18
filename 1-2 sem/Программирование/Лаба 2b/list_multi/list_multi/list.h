#pragma once
#ifndef LIST_CPP
#include <iostream>
#include <Time.h>
#include <vector>
using namespace std;

struct strct {
	int value;
};

class List {
public:

	List();
	~List();

private:

	class Node {
	public:

		Node* pNext;

		strct object;

		Node(int value, Node* pNext = nullptr) {
			this->object.value = value;
			this->pNext = pNext;
		}
	};

	int Size;
	Node* head;

public:
	void append(int value); // push back element
	void push_front(int value);
	strct get(int index); // get element
	void insert(int value, int index); // insert new element by index
	void remove(int index); // remove element by index
	void remove_multi(List& arr, List& lst);
	void length(); // Shows length of list
	int GetSize() { return Size; } // get size of list
	strct& operator[](int index); // operator []
};

List::List()
{
	Size = 0;
	head = nullptr;
}

List::~List()
{
}

void List::append(int value)
{
	if (head == nullptr) {
		head = new Node(value);
		Size++;
	}
	else {
		Node* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(value);
		Size++;
	}
}

void List::push_front(int value)
{
	head = new Node(value, head);
	Size++;
}

strct List::get(int index)
{
	int counter = 0;
	Node* current = this->head;
	while (current != nullptr) {
		if (counter == index) {
			return current->object;
		}
		current = current->pNext;
		counter++;
	}
}

strct& List::operator[](int index)
{
	int counter = 0;
	Node* current = this->head;
	while (current != nullptr) {
		if (counter == index) {
			return current->object;
		}
		current = current->pNext;
		counter++;
	}
}

void List::insert(int value, int index)
{

	if (index == 0) {

		push_front(value);
	}
	else {
		Node* previous = this->head;

		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;

		}
		Node* newNode = new Node(value, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}
}

void List::remove(int index)
{
	Node* previous = this->head;
	for (int i = 0; i < index - 1; i++) {
		previous = previous->pNext;
	}

	Node* toDelete = previous->pNext;
	previous->pNext = toDelete->pNext;
	delete toDelete;
	Size--;
}

void List::remove_multi(List& arr, List& lst)
{
	for (int i = 0; i < arr.GetSize(); i++) {
		strct obj = arr[0];
		int index = obj.value;
		remove(index);
	}
}

void List::length()
{
	cout << "Elements in list: " << Size << endl;
}

void changeSign(List& arr) {
	strct obj;
	for (int i = 0; i < arr.GetSize(); i++) {
		obj = arr[i];
		if (obj.value < 0) {
			int tmp = obj.value;
			tmp = -tmp;
			obj.value = tmp;
		}
	}
}

void bubbleSort(List& arr)
{
	strct obj1,obj2;
	int i, j;
	for (i = 0; i < arr.GetSize() - 1; i++)
		for (j = 0; j < arr.GetSize() - i - 1; j++) {
			obj1 = arr[j];
			obj2 = arr[j + 1];
			if (obj1.value > obj2.value) {
				strct tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
}
#endif LIST_CPP