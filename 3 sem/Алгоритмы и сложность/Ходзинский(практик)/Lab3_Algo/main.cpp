#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>
#include <algorithm>

class Heap {
private:
    int SIZE;
    int capacity;
    int d;
    int* elements;

    void save() {
        int old_c = capacity;
        capacity *= 2;
        int* tmp = elements;
        elements = new int[capacity];
        std::copy(tmp, tmp + old_c, elements);
        delete[] tmp;
    }

    void balance(int index) // збалансування маcиву
    {
        while (true) {
            if (index == 0) {
                break;
            }
            int parent = (index - 1) / d;
            if (elements[index] > elements[parent]) {
                std::swap(elements[index], elements[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void balance_d(int index)
    {
        int max_child,temporary;
        while (true) {
            if ((index * d + 1) >= SIZE) {
                break;
            }
            max_child = -1;
            temporary = elements[index];
            for (int i = 1; i <= d; i++) {
                if (temporary < elements[index * d + i]) {
                    max_child = index * d + i;
                    temporary = elements[index * d + i];
                }
            }
            if (max_child != -1) {
                std::swap(elements[index], elements[max_child]);
                index = max_child;
            }
            else {
                break;
            }
        }
    }

public:
    Heap() = default;

    explicit Heap(int d) {
        this->d = d;
        SIZE = 0;
        capacity = 1;
        elements = new int[capacity];
    }

    void insert(int data) // вставка елементу
    {
        if (SIZE == capacity) {
            save();
        }
        elements[SIZE] = data;
        balance(SIZE);
        SIZE++;
    }

    int Extract_max()// видалити максимальний елемент
    {
        if (SIZE == 0) {
            return 0;
        }
        int res = elements[0];
        elements[0] = elements[SIZE - 1];
        SIZE--;
        balance_d(0);
        return res;
    }

    void increase_key(int key, int step, int index = 0) //збільшити елемент за ключем
    {
        if (index >= SIZE) {
            throw std::invalid_argument("wrong index");
        }
        if (elements[index] == key) {
            elements[index] += step;
            balance(index);
            return;
        }
        for (int i = 1; i <= d; i++) {
            if (elements[index * d + i] >= key) {
                increase_key(key, step, index * d + i);
            }
        }
    }
};

int main() {
    Heap obj;

    /*obj.insert(71);
    obj.insert(13);
    obj.insert(12);
    obj.insert(23);
    obj.insert(6);
    obj.insert(7);
    obj.insert(8);
    obj.insert(0);
    obj.insert()*/
}

void balance(int index)
//Допоміжна функція збалансування масиву
void insert(int data)
//Функція вставки елемента в піраміду
int Extract_max()
//Функція повернення збалансованого масиву, без максимального елементу.
void increase_key(int key, int step, int index)
//Функція збільшення вибраного елементу піраміди