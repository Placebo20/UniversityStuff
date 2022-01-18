#pragma once

#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Time.h>
#include <Vector>
#include "windows.h"
using namespace sf;

struct Player {
public:
	std::string name = "";
	int score = 0;
	static int idg;
	int id = 0;
};



class List {
public:
	List();
	~List();
private:
	struct Node {
		Node* pNext;
		Player object;
		Node(int score, std::string name, Node* pNext = nullptr);
		~Node();
	};
	int Size;
	Node* head;
public:
	void push_back(int score, std::string name);
	void remove(int index);
	int GetSize();
	void push_front(int score, std::string name);
	void insert(int score,std::string name, int index);
	void comparison_bubble();
	Player& operator[](int index);
};

void save_to_txt(List object);
void save_to_bin(List object);
void read_from_bin(List object);