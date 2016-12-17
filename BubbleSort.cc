#include <iostream>
#include <vector>
#include <cassert>
#include "Print.h"
#include "Utils.h"

using namespace std;

void BubbleSort(vector<int>& arr){
    cout << "Main BubbleSort size: " << arr.size() << endl;
    if(arr.size() <= 1){
        return;
    }
    print(arr);
    for(int right = arr.size() - 1; right >= 0; right--){
        for(int left = 0; left < right ; left++){
            if(arr[left] > arr[left + 1]){
                cout << "SWAP : " << arr[left] << " with " << arr[left + 1] << endl;
                swap(arr[left], arr[left + 1]);
                print(arr);
            }
        }
    }
}


bool testBubbleSort(vector<int> &array){
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
