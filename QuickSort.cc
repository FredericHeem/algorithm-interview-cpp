#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Print.h"
#include "Utils.h"
#include <cassert>

using namespace std;

template<typename Iterator>
Iterator Partition(Iterator begin, Iterator end){
    
    auto size = std::distance(begin, end);
    if(size <= 1){
        return begin;
    }
    cout << "Partition size " << size << ", begin: " << *begin << ", end: " << *(end - 1) << endl;
    
    print(begin, end);

    Iterator left = begin;
    Iterator right = end - 1;
    //Pivot in the middle, could be anyone really, this affects performance by the way.
    auto pivotIndex = size / 2;
    auto pivotValue = *std::next(begin, pivotIndex);
    
    cout << "Partition pivot index: " << pivotIndex << ", pivotValue: " << pivotValue << endl;
    
    while(left <= right){
        //cout << "Partition before left: " << *left << ", right: " << *right << endl;
        while(*left < pivotValue){
            left++;
        }
        
        while(*right > pivotValue){
            right--;
        }
        
        //cout << "Partition after left: " << *left << ", right: " << *right << endl;
        if(left < right){
            cout << "Partition  SWAP: " << *left << " with " << *right << endl;
            //print(begin, end);
            std::swap(*left, *right);    
            left++; 
            right--;    
        } else if(left == right){
            break;
        }
    }
   
    
    cout << "Partition DONE" << endl;
    print(begin, end);
    return left;
}

template<typename Iterator>
void QuickSort(Iterator begin, Iterator end, int &level){
    level++;
    cout << "QuickSort begin " << *begin << ", size: " << std::distance(begin, end) << ", level: " << level << endl;
    if(std::distance(begin, end) <= 1){
        return;
    }

    print(begin, end);
    
    if(level > 10){
        cerr << "max level reached " << level << endl;
        return;
    }
    
    Iterator splitIt = Partition(begin, end);
    
    QuickSort(begin, splitIt, level);
    QuickSort(splitIt, end, level);
}

template<class T>
void QuickSort(T& arr){
    cout << "Main QuickSort size: " << arr.size() << endl;
    if(arr.size() <= 1){
        return;
    }
    
    int level = 0;
    
    QuickSort(arr.begin(), arr.end(), level);
}

bool testQuickSort(vector<int> &array){
    print(array);
    QuickSort(array);
    print(array);
    bool equal = isSorted(array);
    cout << "Sorted: " << std::boolalpha << equal << endl;
    assert(equal);
    return equal;
}



int main() {
    cout << "Hello QuickSort" << endl;
    {   
        vector<int> array = {1, 3};
        testQuickSort(array);
    }
    {   
        vector<int> array = {3, 1, 2, 4, 5};
        assert(isSorted(array) == false);
        testQuickSort(array);
    }
    
    {   
        vector<int> array = {1, 5, 6, 3, 4};
        testQuickSort(array);
    }
    
    {   
        vector<int> array = {1, 2, 3, 4, 5};
        testQuickSort(array);
    }
    // Corner Cases
    /*
    {
        vector<int> array = {1};
        const vector<int> arraySorted = {1};
        testQuickSort(array, arraySorted);
    }
    {
        vector<int> array = {};
        const vector<int> arraySorted = {};
        testQuickSort(array, arraySorted);
    }
    */
}
