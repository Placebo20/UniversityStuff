#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "group.h"



class OBSTree {
	struct Node {
		Group* group;
		Node* parent;
		Node* left;
		Node* right;
		double probability{};
		Node() {
			left = right = parent = nullptr;
			probability = 0;
		}
		Node(Group& group, double probability) {
			*this->group = group;
			left = right = parent = nullptr;
			this->probability = probability;
		}
		~Node() = default;
	};
	Node* root;
	std::vector<Group*> groups;
	std::vector<double> probs;
	std::vector<double> fictProbs;

	std::vector<std::vector<double>> expectedValues;
	std::vector<std::vector<double>> probsSum;
	std::vector<std::vector<int>> roots;
	void generateTables() {
		int size = groups.size();
		for (int i = 1; i < size + 2; i++) {
			expectedValues[i][i - 1] = fictProbs[i-1]; //dsds
			probsSum[i][i - 1] = fictProbs[i-1];
		}
		int j;
		double t;
		for (int l = 1; l < size + 1; l++) {
			for (int i = 1; i < size - l + 1; i++) {
				j = i + l - 1;
				expectedValues[i][j] = DBL_MAX;
				probsSum[i][j] = probsSum[i][j - 1] + probs[j - 1] + fictProbs[j];
				for (int r = i; r < j + 1; r++) {
					t = expectedValues[i][r - 1] + expectedValues[r + 1][j] + probsSum[i][j];
					std::cout << "\t";
					if (t < expectedValues[i][j]) {
						expectedValues[i][j] = t;
						roots[i][j] = r;
					}
				}
			}
		}
		std::cout << std::endl;
	}
	Node* constructBST(Node* node, int low, int high) {
		if (low > high) {
			Group* group = new Group();
			std::cout << "Enter the title of group: ";
			std::string title;
			std::cin >> title;
			group->addStudents();
			return new Node(*group, fictProbs[high]);
		}
		int currentIndex = roots[low][high] - 1;
		Node* tempRoot = new Node(*groups[currentIndex], probs[currentIndex]);
		tempRoot->left = constructBST(tempRoot, low, roots[low][high] - 1);
		tempRoot->right = constructBST(tempRoot, roots[low][high] - 1, high);
		tempRoot->parent = node;
		return tempRoot;
	}
	void print(Node* node, int level, bool left) const {
		if (node == nullptr) return;
		if (node == this->root) {
			std::cout << "(Group: " << node->group->getGroupTitle() << std::endl;
			std::cout << "probability " << node->probability << std::endl;
		}
		else {
			for (int i = 0; i < level; i++) std::cout << "|\t";
			if (left) std::cout << "LEFT ";
			else std::cout << "RIGHT ";
			std::cout << "probability " << node->probability << std::endl;
		}
		print(node->left, level + 1, true);
		print(node->right, level + 1, false);
	}
	void erase(Node* toErase) {
		if (toErase == nullptr) return;
		erase(toErase->left);
		erase(toErase->right);
		delete toErase;
	}
public:
	OBSTree(const std::vector<Group*>& groups, const std::vector<double>& probs, const std::vector<double>& fictProbs) {
		this->root = nullptr;
		this->groups = groups;
		this->probs = probs;
		this->fictProbs = fictProbs;

		int size = groups.size();
		this->expectedValues.assign(size + 2, {});
		this->probsSum.assign(size + 2, {});
		this->roots.assign(size + 1, {});

		for (int i = 0; i < size + 2; i++) {
			expectedValues[i].assign(size + 1, 0);
			probsSum[i].assign(size + 1, 0);
		}
		for (int i = 0; i < size + 1; i++) roots[i].assign(size + 1, 0);
		
		generateTables();
		std::cout << "=======================expected groups=======================" << std::endl;
		for (auto& i : expectedValues) {
			for (auto& j : i) {
				std::cout << j << "\t";
			}
			std::cout << "\n";
		}
		std::cout << "=======================probs sum=============================" << std::endl;
		for (auto& i : probsSum) {
			for (auto& j : i) {
				std::cout << j << "\t";
			}
			std::cout << "\n";
		}
		std::cout << "=======================roots=============================" << std::endl;
		for (auto& i : roots) {
			for (auto& j : i) {
				std::cout << j << "\t";
			}
			std::cout << "\n";
		}
		this->root = constructBST(nullptr, 1, size);
	}
	~OBSTree() {
		for (int i = 0; i < groups.size() + 2; i++) {
			expectedValues[i].clear();
			probsSum[i].clear();
		}
		for (int i = 0; i < groups.size() + 1; i++) {
			roots[i].clear();
		}
		expectedValues.clear();
		probsSum.clear();
		roots.clear();
		erase(this->root);
	}
	void print() {
		print(this->root, 0, true);
	}
};