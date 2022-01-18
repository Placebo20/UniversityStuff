#include <iostream>
#include "obsTree.h"
int main() {
	Group* gr1 = new Group("K18");
	Student* st1gr1 = new Student("Ivanov");
	Student* st2gr1 = new Student("Petrov");
	Student* st3gr1 = new Student("Eugenov");
	gr1->addStudent(st1gr1);
	gr1->addStudent(st2gr1);
	gr1->addStudent(st3gr1);

	Group* gr2 = new Group("K28");
	Student* st1gr2 = new Student("Mahnev");
	Student* st2gr2 = new Student("Vitruk");
	Student* st3gr2 = new Student("Kolchishin");
	Student* st4gr2 = new Student("Hushcha");
	gr2->addStudent(st1gr2);
	gr2->addStudent(st2gr2);
	gr2->addStudent(st3gr2);
	gr2->addStudent(st4gr2);

	Group* gr3 = new Group("K19");
	Student* st1gr3 = new Student("Poroshenko");
	gr3->addStudent(st1gr3);

	Group* gr4 = new Group("K29");
	Student* st1gr4 = new Student("Stetsenko1");
	Student* st2gr4 = new Student("Stetsenko2");
	gr4->addStudent(st1gr4);
	gr4->addStudent(st2gr4);

	Group* gr5 = new Group("IPS-31");
	Student* st1gr5 = new Student("Alekseenko");
	Student* st2gr5 = new Student("Kozak");
	gr5->addStudent(st1gr5);
	gr5->addStudent(st2gr5);

	std::vector<Group*> groups = { gr1,gr2,gr3,gr4 };
	std::vector<double> probs = { 0.05, 0.05, 0.05, 0.05, 0.05 };
	std::vector<double> fictProbs = { 0.05, 0.05, 0.05, 0.05, 0.05 };
	auto* tree = new OBSTree(groups, probs, fictProbs);
	tree->print();
	return 0;
}