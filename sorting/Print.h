#include <iostream>
#include <iterator>
#include <algorithm>

template<typename Iterator>
void print(const Iterator& begin, const Iterator& end){
    using T = typename std::iterator_traits<Iterator>::value_type;

    std::for_each(begin, end, [](const T &value){
        std::cout << value << " ";
    });
    
    std::cout << std::endl;
}

template<typename T>
void print(const T &array){
    print(array.begin(), array.end());
}