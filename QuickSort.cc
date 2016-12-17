#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Print.h"

using namespace std;

template<typename Iterator>
Iterator Partition(Iterator begin, Iterator end){
    cout << "Partition begin: " << *begin << ", end: " << *end << endl;
    print(begin, end);
    auto distance = std::distance(begin, end);
    cout << "Partition distance: " << distance << endl;
    
    if(distance <= 0){
        return begin;
    }

    Iterator left = begin;
    Iterator right = end;
    //Pivot in the middle, could be anyone really, this affects performance by the way.
    auto pivotIndex = distance / 2;
    auto pivotValue = *std::next(begin, pivotIndex);
    
    cout << "Partition pivot index: " << pivotIndex << ", pivotValue: " << pivotValue << endl;
    
    while(left <= right){
        cout << "Partition before left: " << *left << ", right: " << *right << endl;
        while(*left < pivotValue){
            left++;
        }
        
        while(*right > pivotValue){
            right--;
        }
        cout << "Partition after left: " << *left << ", right: " << *right << endl;
        if(left <= right){
            cout << "Partition  SWAP: " << *left << " with " << *right << endl;
            //print(begin, end);
            if(left < right){
                std::swap(*left, *right);    
            }
            //print(begin, end);
            left++;
            right--;
        };
    }
   
    
    cout << "Partition DONE left: " << *left << endl;

    return left;
}

template<typename Iterator>
void QuickSort(Iterator begin, Iterator end, int &level){
    level++;
    //cout << "QuickSort begin: " << begin << ", end: " << end << ", level: " << level << endl;
    if(begin >= end){
        return;
    }
    
    Iterator splitIt = Partition(begin, end);

    QuickSort(begin, splitIt - 1, level);
    
    QuickSort(splitIt, end, level);
    
}

void QuickSort(vector<int>& arr){
    cout << "Main QuickSort size: " << arr.size() << endl;
    if(arr.size() <= 1){
        return;
    }
    
    int level = 0;
    
    QuickSort(arr.begin(), arr.end() - 1, level);
}



bool testQuickSort(vector<int> &array, const vector<int> &arraySorted){
    print(array);
    QuickSort(array);
    print(array);
    auto equal = std::equal(array.begin(), array.end(), arraySorted.begin());
    cout << "Sorted: " << std::boolalpha << equal << endl;
    return equal;
}

int main() {
    cout << "Hello QuickSort" << endl;

    {   
        vector<int> array = {1, 5, 6, 3, 4};
        const vector<int> arraySorted = {1, 3, 4, 5, 6};
        testQuickSort(array, arraySorted);
    }
    /*
    {   
        vector<int> array = {1, 2, 3, 4, 5};
        const vector<int> arraySorted = {1, 2, 3, 4, 5};
        testQuickSort(array, arraySorted);
    }*/
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
