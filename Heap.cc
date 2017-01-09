#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

template<class T>
void print(T array){
  for(auto value: array){
    cout << value << " ";
  }
  cout << endl;
}

template<class T>
typename T::const_iterator childLeft(const T&array, typename T::const_iterator it){
  auto distance = std::distance(array.begin(), it);
  if((2 * distance) >= array.size()){
    return array.end();
  }
  return std::next(it, distance + 1);
}

template<class T>
typename T::const_iterator childRight(const T&array, typename T::const_iterator it){
  auto distance = std::distance(array.begin(), it);
  if((2 * distance + 1) >= array.size()){
    return array.end();
  }
  return std::next(it, distance + 2);
}

template<class T>
typename T::const_iterator parent(const T&array, typename T::const_iterator it){
  auto beginIt = array.begin();
  if(array.begin() == it){
    return array.end();
  }

  auto distance = std::distance(beginIt, it);
  return std::next(beginIt, (distance - 1) / 2);
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

int main(){
  testHeapBuild();
}
