#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include "Combination.h"

using namespace std;

int main()
{
    std::cout << "Combination\n";

    vector<string> ruleA {"A1", "A2", "A3"};
    vector<string> ruleB {"B1", "B2"};
    vector<string> ruleC {"C1", "C2"};

    vector<vector<string> > rules;
    rules.push_back(ruleA);
    rules.push_back(ruleB);
    rules.push_back(ruleC);

    vector<vector<string> > outputExpected {
      {{"A1", "B1", "C1"}},
      {{"A1", "B1", "C2"}},
      {{"A1", "B2", "C1"}},
      {{"A1", "B2", "C2"}},
      {{"A2", "B1", "C1"}},
      {{"A2", "B1", "C2"}},
      {{"A2", "B2", "C1"}},
      {{"A2", "B2", "C2"}},
      {{"A3", "B1", "C1"}},
      {{"A3", "B1", "C2"}},
      {{"A3", "B2", "C1"}},
      {{"A3", "B2", "C2"}},         
    };
    CartesianProductStream(rules);
    vector<vector<string> > out = CartesianProduct(rules);
    std::cout << "Combination size " << out.size() << endl;
    std::cout << "Combination outputExpected size  " << outputExpected.size() << endl;
    for(const auto &u: out){
        for(const auto &x: u){
          std::cout << x << " ";
      }
      std::cout << endl;
    }
    assert(out.size() == outputExpected.size());

}
