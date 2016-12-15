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

int Partition(vector<int> &arr, int begin, int end){
    //cout << "Partition begin: " << begin << ", end: " << end << endl;
    
    if(begin >= end){
        return 0;
    }

    int left = begin;
    int right = end;
    int pivotIndex = (end + begin) / 2;
    int pivot = arr[pivotIndex];
    
    cout << "Partition pivot index: " << pivotIndex << ", pivot: " << pivot << endl;
    
    while(left <= right){
        //cout << "Partition before left: " << left << ", right: " << right << endl;
        while(arr[left] < pivot){
            left++;
        }
        
        while(arr[right] > pivot){
            right--;
        }
        //cout << "Partition after left: " << left << ", right: " << right << endl;
        if(left <= right){
            cout << "Partition  SWAP: " << arr[left] << " with " << arr[right] << endl;
            //print(arr);
            swap(arr[left], arr[right]);
            print(arr);
            left++;
            right--;
        };
    }
   
    
    cout << "Partition DONE left: " << left << endl;

    return left;
}

void QuickSort(vector<int>& arr, int begin, int end, int &level){
    level++;
    cout << "QuickSort begin: " << begin << ", end: " << end << ", level: " << level << endl;
    if(begin >= end){
        return;
    }
    
    int splitIndex = Partition(arr, begin, end);
    
    QuickSort(arr, begin, splitIndex - 1, level);
    
    QuickSort(arr, splitIndex, end, level);
    
}

void QuickSort(vector<int>& arr){
    cout << "Main QuickSort size: " << arr.size() << endl;
    if(arr.size() <= 1){
        return;
    }
    int level = 0;
    QuickSort(arr, 0, arr.size() - 1, level);
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
