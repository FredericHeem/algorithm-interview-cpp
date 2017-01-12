#include <iterator>
#include <algorithm>

using namespace std;

template<typename Iterator>
Iterator Partition(Iterator begin, Iterator end){

    Iterator left = begin;
    Iterator right = end - 1;
    auto size = std::distance(begin, end);
    //Pivot in the middle, could be anyone really, this affects performance by the way.
    auto pivotIndex = size / 2;
    auto pivotValue = *std::next(begin, pivotIndex);

    while(left <= right){
        while(*left < pivotValue){
            left++;
        }

        while(*right > pivotValue){
            right--;
        }

        if(left < right){
            std::swap(*left, *right);
            left++;
            right--;
        } else if(left == right){
            break;
        }
    }

    return left;
}

template<typename Iterator>
void QuickSort(Iterator begin, Iterator end){
    if(std::distance(begin, end) <= 1){
        return;
    }

    Iterator splitIt = Partition(begin, end);
    QuickSort(begin, splitIt);
    QuickSort(splitIt, end);
}

template<class T>
void QuickSort(T& arr){
    QuickSort(arr.begin(), arr.end());
}
