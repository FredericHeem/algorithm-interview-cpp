#pragma once
using namespace std;

template<class T>
void BubbleSort(T& arr){
    if(arr.size() <= 1){
        return;
    }
    for(auto right = arr.end(); right >= arr.begin(); --right){
        for(auto left = arr.begin(); left + 1 < right; ++left){
            if(*left > *(left + 1)){
                std::swap(*left, *(left + 1));
            }
        }

    }
}
