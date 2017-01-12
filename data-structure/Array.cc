#include <vector>
#include <iostream>
#include <unordered_set>
#include <cassert>

using namespace std;

template<class T>
void print(T array){
  for(const auto &element : array){
    cout << element << " ";
  }
  cout << endl;
}

using namespace std;
template<typename T>
vector<T> intersection(const vector<T>& arr1, const vector<T>& arr2){
  vector<T> result;
  std::unordered_set<T> set;
  for(const auto& value: arr1){
    set.emplace(value);
  }
  for(const auto& value: arr2){
    const auto inA = set.find(value);
    if(inA != set.end()){
      result.push_back(*inA);
    }
  }

  return result;
};

void testIntersection(){
  vector<int> arr1 {1, 4, 6, 7, 8};
  vector<int> arr2 {4, 7, 9, 20};
  auto result = intersection(arr1, arr2);
  print(result);
  vector<int> expectedResult {4, 7};
  assert(result == expectedResult);
}

int main(){
  cout << "Array" << endl;
  testIntersection();

}
