#include "player.h"

int Player::idg = 0;

List::Node::Node(int score, std::string name, Node* pNext)
{
	this->object.score = score;
	this->object.name = name;
	this->pNext = pNext;
	object.id = object.idg;
	object.idg++;
	std::cout << "Called Node constructor" << std::endl;
}

List::Node::~Node() { std::cout << "Called Node destructor" << std::endl; }

List::List()
{
	Size = 0;
	head = nullptr;
	std::cout << "Called List constructor" << std::endl;
}

List::~List(){ std::cout << "Called List destructor" << std::endl; }

void List::push_back(int score, std::string name)
{
	if (head == nullptr) {
		head = new Node(score, name);
		Size++;
	}
	else {
		Node* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(score, name);
		Size++;
	}
	std::cout << "Called push_back method" << std::endl;
}

void List::remove(int index)
{
	Node* previous = this->head;
	for (int i = 0; i < index - 1; i++) {
		previous = previous->pNext;
	}
	Node* toDelete = previous->pNext;
	delete toDelete;
	Size--;
	std::cout << "Called remove method" << std::endl;
}

int List::GetSize()
{
	return Size;
}

void List::push_front(int score, std::string name)
{
	head = new Node(score,name);
	Size++;
	std::cout << "Called push_front method" << std::endl;
}

void List::insert(int score, std::string name, int index)
{
	if (index == 0) {
		push_front(score, name);
	}
	else {
		Node* previous = this->head;
		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;

		}
		previous->pNext = new Node(score, name,previous->pNext);
		Size++;
	}
	std::cout << "Called insert method" << std::endl;
}

void List::comparison_bubble()
{
	std::cout << "Opened sort method" << std::endl;
	Node* current = head; //head -- указатель на голову
	Node* next = current->pNext; 
	Node* temp = new Node(0,"");

	while (current) {
		next = current->pNext;
		while (next) {
			if ((current->object.score) < (next->object.score)) {

				temp->object.name = current->object.name;
				temp->object.score = current->object.score;

				
				current->object.name = next->object.name;
				current->object.score = next->object.score;

				next->object.name = temp->object.name;
				next->object.score = temp->object.score;

			}
			next = next->pNext;
		}
		
		current = current->pNext;

	}
	std::cout << "Closed sort method" << std::endl;

}

Player& List::operator[](int index)
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

void save_to_txt(List object) {
	std::cout << "Opened save_to_txt method" << std::endl;
	Player tmp;
	std::ofstream txtsave;
	txtsave.open("Highboards.txt");
	if (!txtsave.is_open()) {
		std::cout << "File isn't open. Fuck You!" << std::endl;
	}
	else {
		std::cout << "File is open!Good job!" << std::endl;

		for (int i = 0; i < object.GetSize(); i++) {
			tmp = object[i];
			txtsave << "[" << tmp.id << "] " << tmp.name << ": " << tmp.score << std::endl;
 		}
	}
	txtsave.close();
	std::cout << "Closed save_to_txt method" << std::endl;
}

void save_to_bin(List object) {
	std::ofstream out("bHighboard.txt", std::ios::binary);
	out.write((char*)&object, sizeof(object));
	out.close();
}

void read_from_bin(List object) {
	std::ifstream in("bHighboard.txt", std::ios::binary);
	in.read((char*)&object, sizeof(Player));
	in.close();
}