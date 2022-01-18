#include <iostream>
#include <vector>
using namespace std;


void gnomeSort(vector<double>& vec)
{
    int tmp = 0;

    while (tmp < vec.size()) {
        if (tmp == 0)
            tmp++;
        if (vec[tmp] >= vec[tmp - 1])
            tmp++;
        else {
            swap(vec[tmp], vec[tmp - 1]);
            tmp--;
        }
    }
    return;
}


int main()
{
    
    vector<double> vec = { -8,6,3.1,-1.0,0,16 };
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "  ";
    }
    cout << endl;
    gnomeSort(vec);
    cout << "gnome sorting....." << endl;
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "  ";
    }

    return 0;
}