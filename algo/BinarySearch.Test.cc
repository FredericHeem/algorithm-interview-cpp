#include <iostream>
#include <vector>
#include <cassert>
#include "BinarySearch.h"

using namespace std;

int main()
{
    std::cout << "BinarySearch\n";
    vector<int> arr = {1, 2, 36, 50, 100};
    assert(BinarySearch(arr.begin(), arr.end(), 2));
    assert(BinarySearch(arr.begin(), arr.end(), 40) == false);
}
