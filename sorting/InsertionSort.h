#pragma once
#include <iterator>
#include <algorithm>

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
