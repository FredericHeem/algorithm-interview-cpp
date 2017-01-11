#include <vector>
#include <iostream>
#include <cassert>
#include <utility>

using namespace std;

template<class T>
void print(T array){
  for(auto value: array){
    cout << value << " ";
  }
  cout << endl;
}

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
      swap(*swapIt, *parentIt);
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
void heapSort(T& array){

  heapMake(array);
  for(auto highIt = array.end(); highIt >= array.begin(); highIt--){

    std::swap(*array.begin(), *highIt);
    siftDown(array, array.begin(), highIt);
    //print(array);
  }
}

void testHeapBuild(){
  cout << "testHeapBuild " << endl;
  vector<int> array {1, 4, 6, 2, 8, 7, 10};
  print(array);

  {
    auto it = array.begin();
    assert(*childLeft(array, it) == 4);
    assert(*childRight(array, it) == 6);
    assert(parent(array, it) == array.end());
  }
  {
    auto it = array.begin() + 1;
    assert(*childLeft(array, it) == 2);
    assert(*childRight(array, it) == 8);
    assert(*parent(array, it) == 1);
  }
  {
    auto it = array.begin() + 2;
    assert(*it == 6);
    assert(*childLeft(array, it) == 7);
    assert(*childRight(array, it) == 10);
    assert(*parent(array, it) == 1);
  }
  {
    auto it = array.end();
    assert(childLeft(array, it) == array.end());
    assert(childRight(array, it) == array.end());
    assert(*parent(array, it) == 2);
  }
  {
    vector<int> v {1, 2, 3};
    assert(childLeft(v, v.begin() + 1) == v.end());
    assert(childRight(v, v.begin() + 1) == v.end());
  }
  {
    vector<int> v {1};
    assert(childLeft(v, v.begin()) == v.end());
    assert(childRight(v, v.begin()) == v.end());
  }
  {
    vector<int> v {1, 3};
    assert(*childLeft(v, v.begin()) == 3);
    assert(childRight(v, v.begin()) == v.end());
  }
}
void testHeapifyEven(){
  cout << "testHeapifyEven " << endl;
  vector<int> array {1, 2, 3, 4, 5, 6, 7, 8};
  print(array);
  heapify(array);
  print(array);
  heapify(array);
  print(array);
}

void testHeapifyOdd(){
  cout << "testHeapifyOdd " << endl;
  vector<int> array {1, 2, 3, 4, 5, 6, 7};
  print(array);
  heapify(array);
  print(array);
  heapify(array);
  print(array);
}

void testHeapSort(){
  cout << "testHeapSort " << endl;
  vector<int> array {1, 8, 3, 5, 4, 6, 2, 7};
  print(array);
  heapify(array);
  print(array);
}

int main(){
  testHeapBuild();
  testHeapifyEven();
  testHeapifyOdd();
  testHeapSort();
}
