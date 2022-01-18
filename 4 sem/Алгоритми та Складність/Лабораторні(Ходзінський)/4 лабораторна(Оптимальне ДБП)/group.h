#include "student.h"

class Group {
	std::string title;
	std::vector<Student*> students;
public:
	Group() : title("NULL") {};
	Group(std::string title) {
		this->title = title;
		students.resize(0);
	}
	Group(std::string title, Student* first_student) {
		this->title = title;
		students.push_back(first_student);
	}
 
	std::string getGroupTitle() {
		return title;
	}
	std::vector<Student*> getGroupStudents(){
		return students;
	}

	void setGroupTitle(std::string title) {
		this->title = title;
	}
	void setGroupStudents(std::vector<Student*> students) {
		this->students.clear();
		for (unsigned int i = 0; i < students.size(); i++) {
			this->students.push_back(students[i]);
		}
	}
	void addStudent(Student* student) {
		students.push_back(student);
	}
	void addStudents() {
		std::cout << "Now let's create some students" << std::endl;
		bool stopCreatingStudents = false;
		while (!stopCreatingStudents) {
			Student* newStudent = new Student();
			std::cout << "Type the name of student: ";
			std::string nameOfNewStudent;
			std::getline(std::cin, nameOfNewStudent);
			if (std::cin.fail())break;
			newStudent->setName(nameOfNewStudent);
			this->addStudent(newStudent);
			std::cout << "Stop creating students?(0 - No, 1 - Yes): ";
			std::cin >> stopCreatingStudents;
		}
	}
	void printStudents() {
		for (unsigned int i = 0; i < students.size(); i++) {
			students.at(i)->getStudent();
		}
	}

	bool operator==(Group& gr2) {
		std::cout << "operator==" << std::endl;
		if (this->getGroupStudents().size() == gr2.getGroupStudents().size()) {
			for (unsigned int i = 0; i < gr2.getGroupStudents().size(); i++) {
				if (this->getGroupStudents().at(i) != gr2.getGroupStudents().at(i)) {
					return false;
				}
			}
			return true;
		}
	}
	bool operator!=(Group& gr2) {
		std::cout << "operator!=" << std::endl;
		if (this->getGroupStudents().size() == gr2.getGroupStudents().size()) {
			for (unsigned int i = 0; i < gr2.getGroupStudents().size(); i++) {
				if (this->getGroupStudents().at(i) != gr2.getGroupStudents().at(i)) {
					return true;
				}
			}
			return false;
		}
	}
	bool operator<(Group& gr2) {
		std::cout << "operator<" << std::endl;
		if (this->getGroupStudents().size() < gr2.getGroupStudents().size()) {
			return true;
		}
		else { return false; }
	}
	bool operator>(Group& gr2){
		std::cout << "operator<" << std::endl;
		if (this->getGroupStudents().size() < gr2.getGroupStudents().size()) {
			return false;
		}
		else { return true; }
	}
	Group& operator=(Group& gr2) {
		this->title = gr2.getGroupTitle();
		this->students.clear();
		for (unsigned int i = 0; i < gr2.students.size(); i++) {
			this->students.push_back(gr2.students[i]);
		}
		return *this;
	}
};