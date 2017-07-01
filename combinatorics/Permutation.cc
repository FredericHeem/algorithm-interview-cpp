#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

using namespace std;

void display(const vector<string> &list)
{
    for (const auto &elem : list)
    {
        cout << elem;
    }
    cout << endl;
}

int factorial(int i)
{
    if (i > 1)
    {
        return i * factorial(i - 1);
    }
    return 1;
}

vector<vector<string>> permutation(vector<string> &rule)
{
    vector<vector<string>> out;
    std::sort(rule.begin(), rule.end());

    do
    {
        out.push_back(rule);
    } while (std::next_permutation(rule.begin(), rule.end()));
    return out;
}

int main()
{
    std::cout << "Permutation\n";

    vector<string> rule{"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A10"/*, "A11", "A12"*/};

    vector<vector<string>> out = permutation(rule);

    int permutationSize = factorial(rule.size());
    cout << "permutation size " << permutationSize << endl;
    cout << "out size " << out.size() << endl;
}