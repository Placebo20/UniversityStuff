#include "list.h"

int main() {
	srand(time(NULL));
	List lst;
	strct obj;
	const int max = rand() % 15 + 5;

	for (int i = 0; i < max; i++) {
		lst.append(rand() % 20000 + 0);
	}

	for (int i = 0; i < max; i++) {
		obj = lst[i];
		cout<< "[" << i << "]: " << obj.value << endl;
	}

	cout << endl;
	cout << "How much values you want to delete?: ";
	int count;
	cin >> count;

	while (count > max || count < -max) {
		cout << "Sorry, we dont have so much values in our list.Try again: ";
		cin >> count;
	}
	
	List arr;

	for (int i = 0; i < count; i++) {
		int tmp;
		cout << "Enter " << i + 1 << " value: ";
		cin >> tmp;
		arr.append(tmp);
	}
	changeSign(arr);
	bubbleSort(arr);
	
	for (int i = 0; i < arr.GetSize(); i++) {
		obj = arr[i];
		cout << obj.value << "  ";
	}

	lst.remove_multi(arr, lst);
	cout << endl;
	for (int i = 0; i < lst.GetSize(); i++) {
		obj = lst[i];
		cout << "[" << i << "]: " << obj.value << endl;
	}

}