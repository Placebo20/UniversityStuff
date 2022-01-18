#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int SIZE = 0;
class Student {
	std::string name;
	int STUDENT_ID = 0;
public:
	Student() : name("NULL") {}
	Student(std::string name) {
		this->name = name;
		SIZE++;
		STUDENT_ID = SIZE;
	}
	std::string getName() { return name; }
	void getStudent() { std::cout << "[" << STUDENT_ID << "]: " << name << std::endl; }
	void setName(std::string name) { this->name = name; }
};