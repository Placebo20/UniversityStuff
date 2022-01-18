#include <iostream>
#define n 7
using namespace std;

bool function_KMP(char A[n], char B[n])
//Основна функція, де проходить і порівняння символів, і побудова “таблиці часткового співпадіння”.
{
    int PI[n];

    PI[0] = 0;
    int j = 0, i = 1;
    while (i != n) //формируем масив образа PI
    {
        if (B[i] == B[j])
        {
            PI[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)
        {
            PI[i] = 0;
            i++;
        }
        else
            j = PI[j - 1];
    }
    cout << "A: ";
    for (int q = 0; q < n; q++)
        cout << A[q] << '  ';
    cout << endl;


    cout << "B: ";
    for (int q = 0; q < n; q++)
        cout << B[q] << '  ';
    cout << endl;


    cout << "PI: ";
    for (int q = 0; q < n; q++)
        cout << PI[q] << '  ';
    cout << endl;

    cout << "ANSWER: ";
    int k = 0, l = 0;
    while (l != n)
    {
        if (k == n)
            k = 0;
        if (A[k] == B[l])
        {
            k++;
            l++;
            if (l == n)
            {
                cout << "success";
                return 1;
            }
        }
        else if (l == 0)
        {
            k++;
            if (k == n)
            {
                cout << "fail";
                break;
            }
        }
        else
            l = PI[l - 1];
    }
    return 0;
}


int main()
{
    char A[n]; // = { "qweqwer" };
    char B[n]; // = { "qwerqwe" };
    cout << "A: ";
    for (int i = 0; i < n; i++)
        cin >> A[i];
    cout << "B: ";
    for (int i = 0; i < n; i++)
        cin >> B[i];
    function_KMP(A, B);
}