#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include "BinarySearch.h"

using namespace std;

template<class T>
struct BinarySearchFunctor {
  bool operator()(typename T::iterator begin, typename T::iterator end, const typename T::value_type& value){
    return BinarySearch(begin, end, value);
  }
};

template<class T>
struct BinarySearchRecursiveFunctor {
  bool operator()(typename T::iterator begin, typename T::iterator end, const typename T::value_type& value){
    return BinarySearchRecursive(begin, end, value);
  }
};

template<template<typename> class TBinarySearch>
void testBinarySearch(){
    TBinarySearch<vector<int>> binarySearch;
    vector<int> arr = {99, 1, 2, 36, 50, 100};
    std::sort(arr.begin(), arr.end());
    assert(binarySearch(arr.begin(), arr.end(), 2));
    assert(binarySearch(arr.begin(), arr.end(), 2));
    assert(binarySearch(arr.begin(), arr.end(), 1));
    assert(binarySearch(arr.begin(), arr.end(), 100));
    assert(binarySearch(arr.end(), arr.begin(), 2) == false);
    assert(binarySearch(arr.begin(), arr.end(), 40) == false);
    assert(binarySearch(arr.begin(), arr.end(), 0) == false);
}

int main()
{
    std::cout << "BinarySearch\n";

    //Basic example
    vector<int> arr = {99, 1, 2, 36, 50, 100};
    std::sort(arr.begin(), arr.end());
    assert(BinarySearch(arr.begin(), arr.end(), 2));
    assert(BinarySearch(arr.begin(), arr.end(), 1));
    assert(BinarySearch(arr.begin(), arr.end(), 100));
    assert(BinarySearch(arr.end(), arr.begin(), 2) == false);
    assert(BinarySearch(arr.begin(), arr.end(), 40) == false);
    assert(BinarySearch(arr.begin(), arr.end(), 0) == false);

    testBinarySearch<BinarySearchFunctor>();
    testBinarySearch<BinarySearchRecursiveFunctor>();
}
