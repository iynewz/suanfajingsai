#include <iostream>
#include <sstream>
#include <cstdio>
#include <map>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10000;
map<string, int> name_id_mp;
string id_name_array[maxn];
vector<int> depend[maxn];  // depend[x] 是 x 依赖的列表
vector<int> depend2[maxn]; // depend2[x] 是依赖(使用) x 的列表
int status[maxn];          // 0 - 未安装, 1 - 显式安装, 2 - 作为依赖安装了
vector<int> installed;

int get_id(string name)
{
    if (name_id_mp.find(name) == name_id_mp.end())
    { // 没出现过，分配新编号
        int id = name_id_mp.size();
        name_id_mp[name] = id;
        id_name_array[id] = name;
    }
    return name_id_mp[name];
}

void handle_depend(int o1, stringstream &ss) // stringstream 必须 refer
{
    string object2;

    while (ss >> object2)
    {
        int o2 = get_id(object2);
        depend[o1].push_back(o2);
        depend2[o2].push_back(o1);
    }
}

void install(int item, bool toplevel)
{
    if (status[item] == 0)
    {
        vector<int> dependencies = depend[item];
        for (int i = 0; i < dependencies.size(); i++)
        {
            install(dependencies[i], false);
        }
        cout << "   Installing " << id_name_array[item] << endl;
        status[item] = toplevel ? 1 : 2;
        installed.push_back(item);
    }
}

bool needed(int item)
{
    vector<int> users = depend2[item];
    for (int i = 0; i < users.size(); i++)
    {
        if (status[users[i]] != 0)
        {
            return true;
        }
    }
    return false;
}

void remove(int item, bool toplevel)
{
    if (needed(item) == false)
    {
        if (toplevel == true || status[item] == 2)
        {
            vector<int> dependencies = depend[item];
            status[item] = 0;
            installed.erase(remove(installed.begin(), installed.end(), item), installed.end()); //  C++ algorithm remove

            cout << "   Removing " << id_name_array[item] << endl;

            for (int i = 0; i < dependencies.size(); i++)
            {
                remove(dependencies[i], false);
            }
        }
    }
}

void list()
{
    for (int i = 0; i < installed.size(); i++)
        cout << "   " << id_name_array[installed[i]] << "\n";
}

int main()
{
    string line;
    memset(status, 0, sizeof(status));
    while (getline(cin, line))
    {
        cout << line << endl;
        if (line[0] == 'E')
        {
            break;
        }
        else
        {
            string cmd, object1, object2;
            stringstream ss(line);

            ss >> cmd;
            if (cmd[0] == 'L')
            {
                list();
            }
            else
            {
                ss >> object1;
                int o1 = get_id(object1);

                if (cmd[0] == 'D')
                {
                    handle_depend(o1, ss);
                }
                else if (cmd[0] == 'I')
                {
                    if (status[o1] != 0)
                    {
                        cout << "   " << object1 << " is already installed.\n";
                    }
                    else
                    {
                        install(o1, true);
                    }
                }
                else if (cmd[0] == 'R')
                {
                    if (status[o1] == 0)
                    {
                        cout << "   " << object1 << " is not installed.\n";
                    }
                    else if (needed(o1))
                    {
                        cout << "   " << object1 << " is still needed.\n";
                    }
                    else
                    {
                        remove(o1, true);
                    }
                }
            }
        }
    }
    return 0;
}