#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "QuickSort.h"
#include "Print.h"
#include "Utils.h"
#include <cassert>

using namespace std;

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
        testQuickSort(array);
    });
}
