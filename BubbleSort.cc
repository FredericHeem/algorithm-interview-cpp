#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void print(const T &array){
    for(auto element: array){
        cout << element << " ";
    }
    cout << endl;
}


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



bool testBubbleSort(vector<int> &array, const vector<int> &arraySorted){
    print(array);
    BubbleSort(array);
    print(array);
    auto equal = std::equal(array.begin(), array.end(), arraySorted.begin());
    cout << "Sorted: " << std::boolalpha << equal << endl;
    return equal;
}

int main() {
    cout << "Hello BubbleSort" << endl;

    {   
        vector<int> array = {1, 5, 6, 3, 4};
        const vector<int> arraySorted = {1, 3, 4, 5, 6};
        testBubbleSort(array, arraySorted);
    }
    /*
    {   
        vector<int> array = {1, 2, 3, 4, 5};
        const vector<int> arraySorted = {1, 2, 3, 4, 5};
        testBubbleSort(array, arraySorted);
    }
    */
    // Corner Cases
    /*
    {
        vector<int> array = {1};
        const vector<int> arraySorted = {1};
        testBubbleSort(array, arraySorted);
    }
    {
        vector<int> array = {};
        const vector<int> arraySorted = {};
        testBubbleSort(array, arraySorted);
    }
    */
}
