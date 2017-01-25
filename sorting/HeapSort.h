#pragma once
#include <algorithm>

template<class T>
typename T::iterator childLeft(T& array, typename T::iterator it){
  auto distance = std::distance(array.begin(), it);
  if((2 * distance) >= array.size()){
    return array.end();
  }
  return std::next(it, distance + 1);
}

template<class T>
typename T::iterator childRight(T&array, typename T::iterator it){
  auto distance = std::distance(array.begin(), it);
  if((2 * distance + 1) >= array.size()){
    return array.end();
  }
  return std::next(it, distance + 2);
}

template<class T>
typename T::iterator parent(T&array, typename T::iterator it){
  auto beginIt = array.begin();
  if(array.begin() == it){
    return array.end();
  }

  auto distance = std::distance(beginIt, it);
  return std::next(beginIt, (distance - 1) / 2);
}

// Make sure the parent value is greater than the children
template<class T, class Iterator>
void siftDown(T&array, Iterator lowIt, Iterator highIt){
  Iterator parentIt = lowIt;
  while(childLeft(array, parentIt) < highIt){
    auto left = childLeft(array, parentIt);
    auto right = childRight(array, parentIt);
    auto swapIt = parentIt;
    if(*swapIt < *left){
      swapIt = left;
    }
    if((right < highIt) && (*swapIt < *right)){
      swapIt = right;
    }
    if(swapIt != parentIt){
      std::swap(*swapIt, *parentIt);
      //print(array);
      parentIt = swapIt;
    } else {
      break;
    }
  }
}

template<typename T, typename Iterator>
void heapify(T& array, Iterator beginIt, Iterator endIt){
  auto mid = std::distance(beginIt, endIt) / 2 - 1;
  auto startIt = std::next(beginIt, mid);
  for (auto parentIt = startIt; parentIt >= beginIt; --parentIt) {
    siftDown(array, parentIt, endIt);
  }
}

template<typename T>
void heapify(T& array){
  heapify(array, array.begin(), array.end());
}

template<typename T>
void HeapSort(T& array){

  if(array.size() <= 1){
    return;
  }

  heapify(array);
  for(auto highIt = array.end() - 1; highIt >= array.begin(); highIt--){
    std::swap(*array.begin(), *highIt);
    siftDown(array, array.begin(), highIt);
  }
}
