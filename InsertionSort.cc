#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Print.h"
#include "Utils.h"
#include <cassert>

using namespace std;

template<class T>
void InsertionSort(T& arr){
    if(arr.size() <= 1){
        return;
    }
    
    for(auto wallIt = arr.begin() + 1; wallIt != arr.end(); ++wallIt){
        auto value = *wallIt;
        auto it = wallIt;
        while(it != arr.begin() && *(it - 1) > value){
            *it = *(it - 1);
            it--;
        }
 
        *it = value;
    }
}

bool testInsertionSort(vector<int> &array){
    print(array);
    InsertionSort(array);
    print(array);
    bool equal = isSorted(array);
    cout << "Sorted: " << std::boolalpha << equal << endl;
    assert(equal);
    return equal;
}

int main() {
    cout << "Hello InsertionSort" << endl;
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
        testInsertionSort(array);
    });
}
