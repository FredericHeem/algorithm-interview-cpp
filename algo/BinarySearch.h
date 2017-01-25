#pragma once
#include <iterator>
// Non recursive version of the binary search algorithm with C++11 iterators.
template<class T, class Iterator>
bool BinarySearch(Iterator begin, Iterator end, const T& value){
  auto low = begin;
  auto high = end;

  while(low < high){
    auto distance = std::distance(low, high) / 2;
    auto mid = std::next(low, distance);
    if(*mid == value){
      return true;
    }

    if(distance == 0 && *mid != value){
      return false;
    }

    if(value < *mid){
      high = mid;
    } else {
      low = mid;
    }
  }
  return false;
}

// Recursive version of the binary search algorithm.
template<class Iterator, class T>
bool BinarySearchRecursive(Iterator begin, Iterator end, const T& value){
  auto distance = std::distance(begin, end) / 2;
  auto mid = std::next(begin, distance);
  if(*mid == value){
    return true;
  }

  if(distance == 0 && *mid != value){
    return false;
  }

  if(value < *mid){
    return BinarySearch(begin, mid, value);
  } else {
    return BinarySearch(mid, end, value);
  }
}

