#include <iterator>

template<class Iterator, class T>
bool BinarySearch(Iterator begin, Iterator end, const T& value){
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
