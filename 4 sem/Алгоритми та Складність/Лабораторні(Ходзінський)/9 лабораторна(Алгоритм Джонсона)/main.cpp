#include <iostream>
#include "JohnsonAlgorithm.h"
#include "graph.h"
#include "group.h"
using namespace std;

int main() {

	vector<Group> groups = { {"K11"},{"K12"},{"K13"},{"K14"} };
	Graph g("WGraph2.txt", groups);

	auto v = johnsonAlgorithm(g);
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++)
			cout << " " << v[i][j] << " ";
		cout << endl;
	}
}