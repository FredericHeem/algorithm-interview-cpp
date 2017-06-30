#include <iostream>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

void display(const vector<string> &list){
    for(const auto &elem: list){
        cout << elem;
    }
    cout << endl;
}

int main()
{
    std::cout << "Permutation\n";

    vector<string> ruleA {"A1", "A2", "A3", "A4"};
    std::string s = "aba";
    std::sort(s.begin(), s.end());
    do {
        display(ruleA);
    } while(std::next_permutation(ruleA.begin(), ruleA.end()));
}