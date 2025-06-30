#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

Grammar
read_grammar(istream &in)
{
    Grammar ret;
    string line;
    while (getline(in, line))
    {
        vector<string> entry = split(line);
        if (!entry.empty())
        {
            ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
        }
    }
    return ret;
}