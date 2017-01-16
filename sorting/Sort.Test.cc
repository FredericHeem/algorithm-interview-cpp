#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "SelectionSort.h"
#include "Print.h"
#include "Utils.h"
#include <cassert>

using namespace std;

template<class T>
struct SelectionSortFunctor {
    void operator()(T &arr) { SelectionSort(arr); }
};

template<template<typename> class TSort, class T>
bool testSort(T &array){
    print(array);
    TSort<T> mySort;
    mySort(array);
    print(array);
    bool equal = isSorted(array);
    cout << "Sorted: " << std::boolalpha << equal << endl;
    assert(equal);
    return equal;
}


int main() {
    cout << "Test Sort" << endl;
    vector<vector<int>> testVectors = {
        {1},
        {1, 1},
        {1, 3},
        {3, 1},
        {1, 2, 3},
        {3, 2, 1},
        {3, 1, 2, 4, 5}
    };

    for_each(testVectors.begin(), testVectors.end(), [](vector<int> & array){
        testSort<SelectionSortFunctor>(array);
    });
}
