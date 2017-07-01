#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <math.h>
#include "Combination.h"
#include "Permutation.h"

using namespace std;

void display(const vector<string> &list)
{
    for (const auto &elem : list)
    {
        printf("%s", elem.c_str());
    }
    printf("\n");
}

void display(const vector<vector<string>> &result)
{
    for (const auto &v : result)
    {
        display(v);
    }
}

vector<vector<string>> insertSeparator(const vector<string> &rule)
{
    vector<string> seps{"_", "-", " ", ""};
    vector<vector<string>> out;
    for (auto it = rule.begin(); it != rule.end(); it++)
    {
        if (!(*it).empty())
        {
            out.push_back({*it});
            if (it != rule.end() - 1)
            {
                out.push_back(seps);
            }
        }
    }

    //display(out);
    return out;
}
int rulesCount(const vector<vector<string>> &rules)
{
    //Cartesian product
    int cpCount = 1;
    for (const auto &rule : rules)
    {
        cpCount *= rule.size();
    }
    cout << "cartesian product size " << cpCount << endl;
    int permutationCount = 1;
    for (int i = 1; i <= rules.size(); i++)
    {
        permutationCount *= i;
    }
    cout << "permutationCount " << permutationCount << endl;

    int sepCount = 4;
    int finalCp = pow(sepCount, rules.size() - 1);
    cout << "finalCp " << finalCp << endl;
    int count = cpCount * permutationCount * finalCp;
    cout << "*********rulesCount " << count << endl;
    cout << count / 1000000 << " millions" << endl;
    return count;
}

int main()
{
    std::cout << "Pwgen\n";

    vector<vector<string>> rules;
    rules.push_back({"maxime.beynet@gmail.com", "MAXIME.BEYNET@GMAIL.COM", "mrfreestyleur@free.fr", "MRFREESTYLEUR@FREE.FR"});
    rules.push_back({"ET", "ETHER", "ETHEREUM", "Ether", "Ethereum"});
    rules.push_back({"wallet", "WALLET", "Wallet", "wallets", "WALLETS", "Wallets"});
    rules.push_back({"1", "01", "2", "02"});

    rules.push_back({"vt88q6s2"});
    rules.push_back({"yp3s532g"});
    rules.push_back({"", "Y@"});

    rulesCount(rules);

    vector<vector<string>> cp = CartesianProduct(rules);
    //std::cout << "Combination size " << cp.size() << endl;
    //display(cp);

    for (auto &rule : cp)
    {
        vector<vector<string>> outPerm = permutation(rule);
        std::cout << "permutation size " << outPerm.size() << endl;
        //display(outPerm);
        for (auto &v : outPerm)
        {
            //std::cout << "permutation " << v.size() << endl;
            auto outSep = insertSeparator(v);
            //std::cout << "separator " << outSep.size() << endl;
            //display(outSep);
            //auto outCp = CartesianProduct(outSep);
            CartesianProductStream(outSep);
            //std::cout << "cp " << outCp.size() << endl;
            //display(outCp);
        }
    }
}