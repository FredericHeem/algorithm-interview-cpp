#include <iostream>
#include <vector>
#include <cassert>
#include "Print.h"
#include "Utils.h"

using namespace std;

template<class T>
void BubbleSort(T& arr){
    if(arr.size() <= 1){
        return;
    }
    for(auto right = arr.end(); right >= arr.begin(); --right){
        for(auto left = arr.begin(); left + 1 < right; ++left){
            if(*left > *(left + 1)){
                swap(*left, *(left + 1));
            }
        }
        
    }
}

template<class T>
bool testBubbleSort(T &array){
    print(array);
    BubbleSort(array);
    print(array);
    bool equal = isSorted(array);
    cout << "Sorted: " << std::boolalpha << equal << endl;
    assert(equal);
    return equal;
}

int main() {
    cout << "Hello BubbleSort" << endl;
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
        testBubbleSort(array);
    });
}
