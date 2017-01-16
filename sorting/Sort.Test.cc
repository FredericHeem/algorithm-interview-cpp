#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "Print.h"
#include "Utils.h"
#include <cassert>

using namespace std;

template<class T>
struct SelectionSortFunctor {
    void operator()(T &arr) { SelectionSort(arr); }
};

template<class T>
struct InsertionSortFunctor {
    void operator()(T &arr) { InsertionSort(arr); }
};

template<class T>
struct BubbleSortFunctor {
    void operator()(T &arr) { BubbleSort(arr); }
};

template<class T>
struct HeapSortFunctor {
    void operator()(T &arr) { HeapSort(arr); }
};

template<class T>
struct QuickSortFunctor {
    void operator()(T &arr) { QuickSort(arr); }
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

template<template<typename> class TSort, class T>
void testSortAll(vector<T> &testVectors){
    for_each(testVectors.begin(), testVectors.end(), [](vector<int> & array){
        testSort<TSort>(array);
    });
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

    testSortAll<SelectionSortFunctor>(testVectors);
    testSortAll<InsertionSortFunctor>(testVectors);
    testSortAll<BubbleSortFunctor>(testVectors);
    testSortAll<HeapSortFunctor>(testVectors);
    testSortAll<QuickSortFunctor>(testVectors);
}
