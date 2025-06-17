// The SetStack Computer, UVa 12096
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <stack>
using namespace std;

typedef set<int> Set;
map<Set, int> IDcache; // 把集合映射为 ID, key 是集合；value 是 ID, 从 0 开始编号
vector<Set> Setcache;  // 根据 ID 查找集合

int ID(Set x)
{
    if (IDcache.count(x))
    {
        return IDcache[x]; // 如果集合已经存在，返回它的 ID
    }
    Setcache.push_back(x);
    int id = Setcache.size() - 1;
    IDcache[x] = id; // 将新集合和它的 ID 存入映射
    return id;
}

Set set_union(Set &x1, Set &x2)
{
    Set x = x1;
    x.insert(x2.begin(), x2.end()); // 集合自动去重
    return x;
}

Set set_intersect(Set &x1, Set &x2)
{
    Set x;
    for (Set::iterator it = x1.begin(); it != x1.end(); ++it)
    {
        if (x2.count(*it)) // 如果 x2 中也有这个元素
        {
            x.insert(*it);
        }
    }
    return x;
}

int main()
{
    stack<int> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int op_count;
        cin >> op_count;
        for (int j = 0; j < op_count; j++)
        {
            string op;
            cin >> op;
            if (op[0] == 'P')
            {
                s.push(ID(Set())); // Push a new empty set onto the stack
            }
            else if (op[0] == 'D') // DUP
            {
                s.push(s.top());
            }
            else
            {
                Set x1 = Setcache[s.top()]; // Get the top set
                s.pop();
                Set x2 = Setcache[s.top()];
                s.pop();
                Set x;
                if (op[0] == 'A') // ADD
                {
                    x = x2;
                    x.insert(ID(x1));
                }
                else if (op[0] == 'U') // UNION
                {
                    x = set_union(x1, x2);
                }
                else if (op[0] == 'I') // INTERSECT
                {
                    x = set_intersect(x1, x2);
                }
                s.push(ID(x));
            }
            Set result = Setcache[s.top()];
            cout << result.size() << endl;
        }
        cout << "***\n";
    }
    return 0;
}