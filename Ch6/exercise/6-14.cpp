#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

static const int MAXN = 1005;
vector<int> G[MAXN];
bool vis[MAXN];
int degreeCnt[MAXN];
int V, E, T;

void init()
{
    for (int i = 1; i <= V; i++)
    {
        G[i].clear();
        vis[i] = false;
        degreeCnt[i] = 0;
    }
    return;
}
int odd_count_in_component;

// 遍历一个连通块，并统计其中奇度顶点数量
void dfs(int u)
{
    vis[u] = true;
    if (degreeCnt[u] % 2 == 1)
    {
        odd_count_in_component++;
    }
    for (int v : G[u])
    {
        if (!vis[v])
        {
            dfs(v);
        };
    }
}

int main()
{
    int caseNum = 1;
    while (cin >> V >> E >> T)
    {
        if (V == 0 && E == 0 && T == 0)
        {
            break;
        }
        init();
        for (int i = 0; i < E; i++)
        {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
            degreeCnt[a]++;
            degreeCnt[b]++;
        }
        int total_paths_needed = 0; // 几笔画

        for (int i = 1; i <= V; ++i)
        {
            if (degreeCnt[i] == 0 || vis[i] == true)
            {
                continue;
            }
            odd_count_in_component = 0;
            dfs(i);

            if (odd_count_in_component == 0)
            {
                total_paths_needed += 1;
            }
            else
            {
                total_paths_needed += odd_count_in_component / 2;
            }
        }
        int extra_edges = max(0, total_paths_needed - 1);
        int result = (extra_edges + E) * T;
        cout << "Case " << caseNum++ << ": " << result << "\n";
    }
    return 0;
}