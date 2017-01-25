#pragma once
#include <iterator>
#include <utility>
#include <algorithm>

template<class T>
void SelectionSort(T& arr){
    if(arr.size() <= 1){
        return;
    }

    for(auto it = arr.begin(); it != arr.end(); ++it){
        const auto& max = std::min_element(it, arr.end());
        std::swap(*it, *max);
    }
}
