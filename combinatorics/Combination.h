#pragma once
#include <array>
#include <vector>
#include <list>
#include <sstream>
#include <limits>
using namespace std;

void CartesianProductStream(const vector<vector<string>> &vv)
{
    int cpSize = 1;
    for (const auto &v : vv)
    {
        cpSize *= v.size();
    }
    for (int i = 0; i <= cpSize; i++)
    {
        int nth = i;
        std::string s;
        s.reserve(64);

        for (int j = 0; j < vv.size(); j++)
        {
            auto index = nth % vv[j].size();
            s.append(vv[j][index]);
            nth = nth - index;
            nth = nth / vv[j].size();
        }
        printf("%s\n", s.c_str());
    }
}

vector<vector<string>> CartesianProduct(const vector<vector<string>> &v)
{
    vector<vector<string>> s = {{}};
    for (const auto &u : v)
    {
        vector<vector<string>> r;
        for (const auto &x : s)
        {
            for (const auto y : u)
            {
                r.push_back(x);
                r.back().push_back(y);
            }
        }

        s = move(r);
    }
    return s;
}
