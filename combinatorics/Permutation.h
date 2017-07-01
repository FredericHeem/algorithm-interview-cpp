#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

std::vector<std::vector<std::string>> permutation(std::vector<std::string> &rule)
{
    std::vector<std::vector<std::string>> out;
    std::sort(rule.begin(), rule.end());

    do
    {
        out.push_back(rule);
    } while (std::next_permutation(rule.begin(), rule.end()));
    return out;
}
