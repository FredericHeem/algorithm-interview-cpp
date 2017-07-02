#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <math.h>
#include <fstream>
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
            if (it == rule.begin())
            {
                out.push_back({*it});
            }
            else
            {
                if(!out.empty()){
                    out.push_back(seps);
                }
                out.push_back({*it});
            }
        }
    }

    //display(out);
    return out;
}
struct RulesStat
{
    unsigned long cpSize;
    unsigned long count;
};
int rulesCount(const vector<vector<string>> &rules, RulesStat &stats, ofstream &file)
{
    //Cartesian product
    unsigned long cpCount = 1;
    for (const auto &rule : rules)
    {
        cpCount *= rule.size();
    }
    file << "cartesian product size " << cpCount << endl;
    stats.cpSize = cpCount;
    unsigned long permutationCount = 1;
    for (int i = 1; i <= rules.size(); i++)
    {
        permutationCount *= i;
    }
    file << "permutationCount " << permutationCount << endl;

    int sepCount = 4;
    unsigned long finalCp = pow(sepCount, rules.size() - 1);
    file << "finalCp " << finalCp << endl;
    unsigned long count = cpCount * permutationCount * finalCp;
    file << "RulesCount " << count << endl;
    file << count / 1000000 << " millions" << endl;
    file << count / 400000 / 3600 << " hours" << endl;
    stats.count = count;
    return count;
}

int main()
{
    std::cout << "Pwgen\n";
    ofstream file;
    file.open("pwgen.log");
    vector<vector<string>> rules;
    rules.push_back({
                     "maxime.beynet@gmail.com", "MAXIME.BEYNET@GMAIL.COM",
                     ""
                     //"maxime;beynet@gmail;com", "MAXIME;BEYNET@GMAIL;COM"
                     //"mrfreestyleur@free.fr", "MRFREESTYLEUR@FREE.FR",
                     //"mrfreestyleur@free;fr", "MRFREESTYLEUR@FREE;FR"
                     });
    rules.push_back({"ET", "ETHER", "ETHEREUM", "Ether", "Ethereum", "ETH", "Eth", ""});

    rules.push_back({"wallet", "WALLET", "Wallet", "wallets", "WALLETS", "Wallets", ""});
    rules.push_back({"2", "02"});

    rules.push_back({"vt88q6s2"});
    rules.push_back({"yp3s532g"});
    rules.push_back({"", "Y@"});

    RulesStat stats;
    rulesCount(rules, stats, file);

    vector<vector<string>> cp = CartesianProduct(rules);
    int cpIndex = 0;
    unsigned long total = 0;
    for (auto &rule : cp)
    {
        vector<vector<string>> outPerm = permutation(rule);
        cpIndex++;
        file << "cp index " << cpIndex << "/" << stats.cpSize << " " << cpIndex * 100 / stats.cpSize << "%" << endl;
        unsigned long cpSize = 0;
        //display(outPerm);
        for (auto &v : outPerm)
        {
            auto outSep = insertSeparator(v);
            cpSize += CartesianProductStream(outSep);

        }
        total += cpSize;
        file << "Total " << total / 1000000 << " millions, cpSize " << cpSize << endl;
        
    }
    
    file.close();
}