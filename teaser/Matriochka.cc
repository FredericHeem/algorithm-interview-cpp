#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include "Matriochka.h"

using namespace std;


int main()
{
    std::cout << "Matriochka\n";

    Box child(1, 1, 1);
    Box father(2, 2, 2);
    assert(isChildren(father, child));
    assert(!isChildren(child, father));

    vector<Box> boxes {
      {Box(1, 1, 1)},
      {Box(3, 3, 3)},
      {Box(4, 4, 4)},
      {Box(2, 2, 2)}
    };

    auto result = Matrioska(boxes);
    std::cout << "Matrioska " << result;
    //assert(Matrioska(boxes) == 3);

}
