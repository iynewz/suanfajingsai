#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

const int maxn = 1000 + 5;
int bfs[maxn];
int b_pos[maxn]; // b[value]
int dfs[maxn];
vector<int> adj[maxn];

void solve(int l, int r)
{
    if (l == r)
    {
        return;
    }
    int root = dfs[l];
    int i = l + 1;
    int lasti = i;

    adj[root].push_back(dfs[i]); // 如果程序可以运行到这里，那么一定可以记录第一个孩子
    i++;
    while (i <= r)
    { // root 一共有几个孩子？处理所有的孩子的子树
        int v = dfs[i];
        int lastv = adj[root].back();

        if ((b_pos[v] - b_pos[lastv] == 1) && v > lastv)
        {
            // 说明 v 是同级的孩子
            adj[root].push_back(v);
            solve(lasti, i - 1); // 上一棵子树的 DFS 区间
            lasti = i;
        }
        i++;
    }
    solve(lasti, i - 1); // 最后一个，因为右指针跳出循环了所以没有处理到，要补一下
}

int main()
{
    int n;
    while (cin >> n)
    {
        memset(bfs, 0, sizeof(bfs));
        memset(dfs, 0, sizeof(dfs));
        for (int i = 1; i <= n; i++)
        {
            adj[i].clear();
            cin >> bfs[i];
            b_pos[bfs[i]] = i;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> dfs[i];
        }
        solve(1, n);

        for (int i = 1; i <= n; i++)
        {
            cout << i << ":";
            int len = adj[i].size();
            for (int j = 0; j < len; j++)
            {
                cout << " " << adj[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}