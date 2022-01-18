#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;

//Task 2.1, 2.2
double function(int num){
    if(num > 0){
        return sin(5*num +172);
    } else if(num < 0){
        return log(pow(abs(num), 7) + 272) / log(2);
    } else return 0;
}

//Task 2.3
double function(double num){
    //f(d) = d/(d+472)f
    return num/(num + 472);
}

//Task 2.4
double function(std::string str){
    double integers = 0;
    for(int i = 0; i < str.length(); i++){
        if(isdigit(str[i])) integers++;
    }
    return integers/str.length();
}

//Task 2.5
template <typename T>
double function(std::string first, T second){
    return pow(first.length(),sin(572 * second));
}

template <typename T>
double function(T first, std::string second){
    return pow(first,sin(572 * second.length()));
}

template<typename T1, typename T2>
double function(T1 first, T2 second) {
    //f(p) = f(b)^(sin(572*f(a)))
    return pow(first,sin(572 * second));
}

//Task 2.6
template<typename T>
double function(std::vector<T> v){
    //f(v) = min cos(f(v) - 772)
    std::vector<T> buffer;
    for(int i = 0; i < v.size(); i++){
        T tmp = cos(v[i] - 772);
        buffer.push_back(tmp);
    }
    T minimum = 0;
    for(int i = 0; i < buffer.size(); i++){
        if(buffer[i] < minimum){
            minimum = buffer[i];
        }
    }
    return minimum;
}

//Task 2.7
template<typename anotherType>
double function(anotherType x){
    return 35.72;
}

void demo() {
    cout << "Hello, first is \"double function(int num), if num > 0 (3)\"" << endl;
    int num = 3;
    cout << function(num) << endl;
    cout << "==================================================================" << endl;
    cout << "Now if num < 0 (-3)" << endl;
    num = -3;
    cout << function(num) << endl;
    cout << "==================================================================" << endl;
    cout << " Now \"double function(double num)\" (2.5)" << endl;
    double dnum = 2.5;
    cout << function(2.5) << endl;
    cout << "==================================================================" << endl;
    cout << "Now \"double function(std::string str)\" (\" aBd32D3324sc (6/12)\")" << endl;
    std::string str = "aBd32D3324sc";
    cout << function(str) << endl;
    cout << "==================================================================" << endl;
    cout << "Now \"double function(T1 first, T2 second)\".(int = 3, double = 5.5)" << endl;
    num = 3; dnum = 5;
    cout << function(3,5.5) << endl;
    cout << "==================================================================" << endl;
    cout << "Now \"double function(std::vector<T> v)\" (v = {1,2,3,5,-2,4,21})" << endl;
    std::vector<int> v = {1,2,3,5,-2,4,21};
    cout << function(v) << endl;
    cout << "==================================================================" << endl;
    cout << "Now \"double function(anotherType x)\"(float = 0.1)" << endl;
    float x = 0.1;
    cout << function(x);
}

int main() {
    demo();
    return 0;
}
