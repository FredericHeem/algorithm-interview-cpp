#include <vector>
#include <iostream>
#include <cassert>
#include <utility>
#include "HeapSort.h"

using namespace std;

template<class T>
void print(T array){
  for(auto value: array){
    cout << value << " ";
  }
  cout << endl;
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
  heapSort(array);
  print(array);
}

int main(){
  testHeapBuild();
  testHeapifyEven();
  testHeapifyOdd();
  testHeapSort();
}
