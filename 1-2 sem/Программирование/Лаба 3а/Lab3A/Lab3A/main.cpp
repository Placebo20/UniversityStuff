#include "Mode.h"


int main (){
	
	vector <double> myvec = { 4,-9,1.5,0,2,64,65.5,-78 };
	int Mode;
	cout << "Choose mode\n1)Demonstration\n2)Benchmark" << endl;
	cin >> Mode;
	switch (Mode) {
	case 1:
		demo(myvec);
		break;
	case 2:
		bench(myvec);
		break;
	default:
		break;
	}
	return 0;
}