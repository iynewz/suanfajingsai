//not finished
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;
const int maxn = 100 + 5;

vector<int> tokens;
struct T
{
    vector<int> P_in;
    vector<int> P_out;
};
T transitions[maxn];

bool can_transition_fire(int i)
{
    return tokens[i] >= transitions[i].P_in;
}

void fire(int i)
{
    tokens[i] -= transitions[i].P_in;
    int end = i + 1;
    if(end >  )
}

int main()
{
    int NP, NT, NF;
    int case_num = 1;

    while (cin >> NP && NP)
    {
        tokens.clear();
        for (int i = 1; i <= NP; i++)
        {
            int tmp;
            cin >> tmp;
            tokens.push_back(tmp);
        }
        cin >> NT;
        for (int i = 1; i <= NT; i++)
        {
            transitions[i].P_in.clear();
            transitions[i].P_out.clear();
            int temp;
            while (cin >> temp && temp)
            {
                if (temp < 0)
                {
                    transitions[i].P_in.push_back(abs(temp));
                }
                else
                {
                    transitions[i].P_out.push_back(temp);
                }
            }
        }
        cin >> NF;

        // simulate
        for (int i = 1; i <= NF; i++) // 遍历 NF 次
        {
            for (int j = 1; j <= NT; j++)
            {
                if (can_transition_fire(j))
                {
                    fire(j);
                    break;
                }
            }
        }
    }

    return 0;
}