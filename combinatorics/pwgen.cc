#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include "Combination.h"

using namespace std;

void display(const vector<string> &list){
    for(const auto &elem: list){
        cout << elem;
    }
    cout << endl;
}

void display(const vector<vector<string>> &result){
    for(const auto &v: result){
        display(v);
    }
    cout << endl;
}


int main()
{
    std::cout << "Pwgen\n";

    vector<string> ruleA {"A1", "A2", "A3"};
    vector<string> ruleB {"B1", "B2"};
    vector<string> ruleC {"C1", "C2"};

    vector<vector<string> > rules;
    rules.push_back(ruleA);
    rules.push_back(ruleB);
    rules.push_back(ruleC);

    vector<vector<string> > out = CartesianProduct(rules);
    std::cout << "Combination size " << out.size() << endl;
    display(out);
}