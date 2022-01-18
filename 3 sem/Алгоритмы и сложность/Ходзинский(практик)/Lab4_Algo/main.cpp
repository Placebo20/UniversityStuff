#include <iostream>
#include <vector>

using namespace std;

int len(int m) {//допоміжна функція яка знаходить розрядність числа
    int cnt = 0;
    while (m) {
        m /= 10;
        cnt++;
    }
    return cnt;
}

void print(vector <pair <int, char>> a, int n) {//допоміжна функція яка виводить масив на екран
    for (int i = 0; i < n; i++) {
        cout << a[i].first;
        cout << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i].second << " ";
    }
    cout << "\n---------------------------------\n";
}

void copy(vector<pair<int, char>>& a, vector<pair<int, char>> b) {//допоміжна функція яка копіює один вектор в інший
    for (int i = 0; i < b.size(); i++)
        a[i] = b[i];
}

void first_sort(vector <pair <int, char>>& a, int n) { //  функція виконує сортування з час О(n) яке є стійким
    vector <pair <int, char>> result;
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first == 0)
            result.push_back(a[i]);
    }
    for (int i = 0; i < n; i++) {
        if (a[i].first == 1)
            result.push_back(a[i]);
    }

    copy(a, result);
}

void second_sort(vector <pair <int, char>>& a) { // ) функція виконує стійке сортування яке проводиться на місці
    int cnt = 0;
    int n = a.size();
    bool flag = true;
    while (flag) {
        flag = false;
        for (int j = 0; j < n - 1; j++) {
            if (a[j].first > a[j + 1].first) {
                swap(a[j], a[j + 1]);
                flag = true;
            }
        }
    }
}

void third_sort(vector <pair <int, char>>& a, int n) { //  функція  виконує сортування за час О(n) та прoводиться на місці
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first == 0) {
            swap(a[p], a[i]);
            p++;
        }
    }
}

int main()
{
    srand((unsigned)(NULL));
    int n = 10;
    vector<pair<int, char>> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        a[i].first = rand() % 2;
        a[i].second = rand() % 100 + '0';
    }
    copy(b, a);
    copy(c, a);
    print(a, 10);

    cout << "sort  with characteristics( O(n) and stable)" << endl;
    first_sort(b, 10);
    print(b, 10);

    second_sort(c);
    cout << "sort with characteristics (stable and O(1) additional memory)" << endl;
    print(c, 10);

    third_sort(a, 10);
    cout << "sort  with characteristics   (O(n) of time and O(1) memory)" << endl;
    print(a, 10);
}




