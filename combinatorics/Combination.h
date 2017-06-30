#pragma once
#include <array>
#include <vector>
#include <list>
#include <limits>
using namespace std;

vector<vector<string>> CartesianProduct (const vector<vector<string>>& v) {
    vector<vector<string>> s = {{}};
    for (const auto& u : v) {
        vector<vector<string>> r;
        for (const auto& x : s) {
            for (const auto y : u) {
                r.push_back(x);
                r.back().push_back(y);
            }
        }
        std::cout << "CartesianProduct MOVE r.size " << r.size() << endl;
        for(const auto& elems: r){
          std::cout << elems.size() << " ";
          for(const auto& elem : elems){
            std::cout << elem << " ";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
        s = move(r);
    }
    return s;
}

