#pragma once
#ifndef HEADER_H
#include "Sorts.h"

void demo(vector<double>& vec) {
	cout << "You chose Demonstraition mode. Now we have this vector:" << endl;
	PrintVector(vec);
	cout << "Now we will use a bubble sort" << endl;
	BubbleSort(vec);
	cout << "bubble sort is working..." << endl;
	PrintVector(vec);
	cout << "Okay, let's shuffle vector" << endl;
	Shuffle(vec);
	cout << "shuffling.." << endl;
	PrintVector(vec);
	cout << "Now we wil use a quick sort(lomuto, rightmost pivot)" << endl;
	int n = sizeof(vec) / sizeof(vec[0]);
	quickSort(vec, 0, vec.size() - 1);
	cout << "quick sort is working..." << endl;
	PrintVector(vec);
	cout << "Okay, let's shuffle vector" << endl;
	Shuffle(vec);
	cout << "shuffling.." << endl;
}

void bench(vector<double>& vec) {

}

#endif HEADER_H