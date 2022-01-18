#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;
using std::cin;

class Date {
public:
	int day;
	int month;
	int year;
};

class List {
public:

	List();
	~List();
	
private:
	
	class Node {
	public:

		Node* pNext;
		
		Date object;

		Node(int day, int month, int year, Node* pNext = nullptr) {
			this->object.day = day;
			this->object.month = month;
			this->object.year = year;
			this->pNext = pNext;
		}
	};

	int Size;
	Node* head; //Указатель на первый элемент списка

public:

	void append(int day, int month, int year); // Добавляет элемент в конец списка
	Date get(int index); // Геттер структуры == элемента класса 
	void set(int day, int month, int year, int index); // Сеттер структуры == элемента класса
	void create_empty(int value); // Создаёт пустой список размером value
	void insert(int day, int month, int year, int index); // Вставляет новый элемент по индексу index
	void remove(int index); // Удаляет элемент по индексу index
	void length(); // Выводит список
	int GetSize() { return Size; } // Геттер размера списка
	void push_front(int day, int month, int year); // Добавляет элемент в начало списка
	Date& operator[](int index); // Оператор обращения к элементу
};



List::List()
{
	Size = 0;
	head = nullptr;
}

List::~List()
{
}

void List::append(int day, int month, int year) 
{
	if (head == nullptr) {
		head = new Node(day, month, year);
		Size++;
	}
	else {
		Node* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(day, month, year);
		Size++;
	}
}

Date List::get(int index) 
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

Date& List::operator[](int index)				
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

void List::set(int day, int month, int year, int index) 
{
	int counter = 0;
	Node* current = this->head;
	while (current != nullptr) {
		if (counter == index) {
			current->object.day = day;
			current->object.month = month;
			current->object.year = year;
		}
		current = current->pNext;
		counter++;
	}
}

void List::create_empty(int value) 
{
	for (int i = 0; i < value; i++) {
		append(0, 0, 0);
	}
}

void List::push_front(int day, int month, int year) 
{
	head = new Node(day, month, year, head);
	Size++;
}

void List::insert(int day, int month, int year, int index)
{
	
	if (index == 0) {

		push_front(day,month,year);
	}
	else {
		Node* previous = this->head;
		
		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
				
		}
		Node* newNode = new Node(day, month, year, previous->pNext);
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

void List::length() 
{cout << "Elements in list: " << Size << endl;}



void menu(int &choose, int &mode) {

	cout << "Choose mode:\n"
		"1)Interactive\n"
		"2)Demonstration\n"
		"3)Benchmark\n" << endl;
	cin >> mode;
	system("cls");
	
	if (mode == 1) {
		cout << "What do yo want to do?(Choose from 1 to ):\n"
			"1)Create empty list\n"
			"2)Push some elements in list\n"
			"3)Create list with random values\n"
			"4)Exit" << endl;
		cin >> choose;

		while (choose < 1 || choose > 4) {
			cout << "Incorrect input, try again: ";
			cin >> choose;
		}
	}
}

void Interactive(int choose) {

	List lst;
	Date tmp;

	if (choose == 1) {
		int emptyListValue = 0;
		cout << "How much elements of empty list you want to create?: ";
		cin >> emptyListValue;
		lst.create_empty(emptyListValue);
	}
	else if (choose == 2) {
		int appendValue = 0;
		int	appendType = 0;
		cout << "What type of push you want to use?(Front(1) or Back(2) push): ";
		cin >> appendType;
		cout << "How much elements you want to push?" << endl;
		if (appendType == 1) {
			for (int i = 1; i <= appendValue; i++) {
				int day, month, year;

				cout << i << "\nDay: ";
				cin >> day;
				cout << "Month: ";
				cin >> month;
				cout << "Year: ";
				cin >> year;

				lst.push_front(day, month, year);
				cout << "=====================" << endl;
			}
		}
		else if (appendType == 2) {
			for (int i = 1; i <= appendValue; i++) {
				int day, month, year;

				cout << i << "\nDay: ";
				cin >> day;
				cout << "Month: ";
				cin >> month;
				cout << "Year: ";
				cin >> year;

				lst.append(day, month, year);
				cout << "=====================" << endl;
			}
		}
	}
	else if (choose == 3) {
		int randomValues;
		cout << "How much values you want to create?: " << endl;
		cin >> randomValues;
		for (int i = 0; i < randomValues; i++) {
			lst.append((1 + rand() % 31), (1 + rand() % 12), (1900 + rand() % 120));
		}
	}
	else {
		exit(1);
	}

		cout << "What to do now?\n"
			"1)Append one value\n"
			"2)Remove one value by index\n"
			"3)Show me my list\n"
			"4)Show me one value by index\n"
			"5)Set some values by index\n"
			"6)Insert one element by index\n"
			"7)Exit" << endl;
		cin >> choose;

		if (choose == 1) {

			int day, month, year;

			cout << "Day: ";
			cin >> day;
			cout << "Month: ";
			cin >> month;
			cout << "Year: ";
			cin >> year;
			lst.append(day, month, year);

		}
		else if (choose == 2) {
			int index;
			cout << "Index(from 0 to " << lst.GetSize() - 1 << "): ";
			cin >> index;
			lst.remove(index);
		}
		else if (choose == 3) {
			for (int i = 0; i < lst.GetSize(); i++) {
				tmp = lst[i];
				cout << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
			}
		}
		else if (choose == 4) {
			int index;
			cout << "Index(from 0 to " << lst.GetSize() - 1 << "): ";
			cin >> index;
			tmp = lst.get(index);
			cout << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
		}
		else if (choose == 5) {
			int index;
			cout << "Index(from 0 to " << lst.GetSize() - 1 << "): ";
			cin >> index;
			int day, month, year;
			cout << "Day: ";
			cin >> day;
			cout << "Month: ";
			cin >> month;
			cout << "Year: ";
			cin >> year;

			lst.set(day, month, year, index);
		}
		else if (choose == 6) {
			int index;
			cout << "Index(from 0 to " << lst.GetSize() - 1 << "): ";
			cin >> index;
			int day, month, year;
			cout << "Day: ";
			cin >> day;
			cout << "Month: ";
			cin >> month;
			cout << "Year: ";
			cin >> year;

			lst.insert(day, month, year, index);
		}
		else { exit(1); }

		cout << "================" << endl;
		cout << "Do you want to output your data?(1 - yes, 0 - no)" << endl;
		cin >> choose;
		if (choose == 1) {
			lst.length();
			for (int i = 0; i < lst.GetSize(); i++) {
				tmp = lst[i];
				cout << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
			}
		}
		else {
			exit(1);
		}
		
}

void Demonstration() {

	List lst;
	Date tmp;
	cout << "So, I will show how this lab works..." << endl;
	system("pause");
	system("cls");


	//create_empty(5);
	cout << "Let's create an empty list with 5 elements\ncreate_empty(int value) works..." << endl << endl;
	lst.create_empty(5);
	cout << "And now let's cout this list" << endl;
	lst.length();
	cout << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		tmp = lst[i];
		cout <<	"[" << i << "] " <<tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
	}
	cout << endl;
	system("pause");
	system("cls");


	//append(10, 12, 2020);
	cout << "Now we append one elemetn day - 10, month 12, year - 2020\nappend(10, 12, 2020) works..." << endl;
	lst.append(10, 12, 2020);
	cout << endl;
	cout << "And lets look at our changes" << endl << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		tmp = lst[i];
		cout << "[" << i << "] " << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
	}
	cout << endl;
	system("pause");
	system("cls");


	//insert(1, 1, 1000, 2);
	cout << "Also we can insert an element by index(index = 2, and day = 1, month 1, year = 1000)\ninsert(1, 1, 1000, 2) works..." << endl;
	lst.insert(1, 1, 1000, 2);
	cout << endl;
	cout << "And lets look at our changes" << endl << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		tmp = lst[i];
		cout << "[" << i << "] " << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
	}
	cout << endl;
	system("pause");
	system("cls");


	//remove(1);
	cout << "Let's remove one element(by index = 1)\nremove(1) works..." << endl;
	lst.remove(1);
	cout << endl;
	cout << "And lets look at our changes" << endl << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		tmp = lst[i];
		cout << "[" << i << "] " << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
	}
	cout << endl;
	system("pause");
	system("cls");


	//set(6, 6, 666, 4);
	cout << "Also, this lab have a setter method, lets set a values by index(index = 4, day = 6, month = 6, year = 666)\nset(6, 6, 666, 4) works..." << endl;
	lst.set(6, 6, 666, 4);
	cout << endl;
	cout << "And lets look at our changes" << endl << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		tmp = lst[i];
		cout << "[" << i << "] " << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
	}
	cout << endl;
	system("pause");
	system("cls");


	//get(5);
	cout << "We can get one element from list by index(index = 5)\nget(5) works..." << endl << endl;
	cout << "Our list:" << endl << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		tmp = lst[i];
		cout << "[" << i << "] " << tmp.day << "/" << tmp.month << "/" << tmp.year << endl;
	}
	cout << endl;
	cout << "Our element by index 5" << endl << endl;
	tmp = lst.get(5);
	cout << "[" << 5 << "] " << tmp.day << "/" << tmp.month << "/" << tmp.year << endl << endl << endl;

	cout << "THANKS FOR ATTENTION :D" << endl << endl;

}

int main() {
	
	int choose, mode;
	menu(choose, mode);
	if (mode == 1) {
		Interactive(choose);
	}
	else if (mode == 2) {
		Demonstration();
	}
	else {
		//Benchmark();
	}
	return 0;
}