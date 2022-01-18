#pragma once
#ifndef SORTS_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void BubbleSort(vector<double>& vec){

    const int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                double tmp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = tmp;
            }
        }
    }

}

int partition(vector<double>& vec, int l, int h)
{
    int pivot = vec[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++)
    {
        if (vec[j] <= pivot)
        {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[h]);
    return (i + 1);
}

void quickSort(vector<double>& vec, int l, int h)
{
    if (l < h)
    {
        int pi = partition(vec, l, h);

        quickSort(vec, l, pi - 1);
        quickSort(vec, pi + 1, h);
    }
}

void Shuffle(vector<double>& vec) {
    auto rng = std::default_random_engine{};
    shuffle(begin(vec), end(vec), rng);
}

//Ефективний алгоритм сортування merge sort top - down, two arrays
void MergeSort(vector<double>& vec) {

}

void PrintVector(vector<double>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "  ";
    }
    cout << endl;
}

#endif SORTS_H