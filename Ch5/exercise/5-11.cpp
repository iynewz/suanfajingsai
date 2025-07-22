#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

map<string, string> mp1; // 第一行字典
map<string, string> mp2; // 第一行字典
vector<string> new_key;
vector<string> removed;
vector<string> changed;

void parse(const string &s, map<string, string> &target_map)
{
    int len = s.length();
    string k, v;
    int key_flag = 1;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '{')
        {
            continue;
        }
        if (s[i] == ':')
        {
            key_flag = 0;
            continue;
        }
        if (key_flag && s[i] != '}') // 第一次漏了这里的  != '}'
        {
            k += s[i];
        }
        if (!key_flag && s[i] != ',' && s[i] != '}')
        {
            v += s[i];
        }
        if (s[i] == '}' || s[i] == ',')
        {
            key_flag = 1;
            if (!k.empty())
            {
                target_map[k] = v;
            }
            k.clear();
            v.clear();
        }
    }
}

void test_print_map(const map<string, string> &target_map)
{
    cout << "Map contents:" << endl;
    for (const auto &pair : target_map)
    {
        cout << "Key: '" << pair.first << "', Value: '" << pair.second << "'" << endl;
    }
    cout << "---------------------" << endl;
}

int main()
{
    int T;
    cin >> T;
    getchar();
    while (T--)
    {
        mp1.clear();
        mp2.clear();
        new_key.clear();
        removed.clear();
        changed.clear();

        string l1, l2;
        getline(cin, l1);
        getline(cin, l2);
        parse(l1, mp1);
        parse(l2, mp2);
        // test_print_map(mp1);
        // test_print_map(mp2);

        // compare
        for (const auto &pair : mp2)
        {
            if (!mp1.count(pair.first))
            {
                new_key.push_back(pair.first);
            }
            else
            {
                if (pair.second != mp1[pair.first])
                {
                    changed.push_back(pair.first);
                }
            }
        }
        for (const auto &pair : mp1)
        {
            if (!mp2.count(pair.first))
            {
                removed.push_back(pair.first);
            }
        }

        // print out
        if (!new_key.empty())
        {
            cout << '+';
            for (size_t i = 0; i < new_key.size(); ++i)
            {
                cout << new_key[i];
                if (i != new_key.size() - 1) // 如果不是最后一个元素
                {
                    cout << ',';
                }
            }

            cout << endl;
        }

        if (!removed.empty())
        {
            cout << '-';
            for (size_t i = 0; i < removed.size(); ++i)
            {
                cout << removed[i];
                if (i != removed.size() - 1) // 如果不是最后一个元素
                {
                    cout << ',';
                }
            }
            cout << endl;
        }

        if (!changed.empty())
        {
            cout << '*';
            for (size_t i = 0; i < changed.size(); ++i)
            {
                cout << changed[i];
                if (i != changed.size() - 1) // 如果不是最后一个元素
                {
                    cout << ',';
                }
            }
            cout << endl;
        }

        if (new_key.empty() && removed.empty() && changed.empty())
        {
            cout << "No changes" << endl;
        }
        cout << endl;
    }

    return 0;
}