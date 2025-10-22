#include <iostream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 100 + 5;
int n, m, u, v, t;
int G[maxn][maxn];
int topo[maxn];
int c[maxn]; // c[v] 0 - 还未开始访问; -1 - 访问中; 1 - 已访问

void dfs(int u)
{
    c[u] = -1; // 标记为访问中
    for (int v = 1; v <= n; v++)
    {
        if (G[u][v] == 1)
        {
            if (c[v] == -1)
            {
                return;
            }
            else if (c[v] == 0)
            {
                dfs(v);
            }
        }
    }
    c[u] = 1; // 标记为已访问
    topo[t] = u;
    t--;
}
void toposort()
{
    t = n;
    memset(c, 0, sizeof(c));
    for (int u = 1; u <= n; u++)
    {
        if (c[u] == 0)
        {
            dfs(u);
        }
    }
    return;
}

int main()
{
    while (scanf("%d %d", &n, &m) == 2 && n)
    {
        memset(G, 0, sizeof(G)); // 忘了：清空图
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &u, &v);
            G[u][v] = 1;
        }
        toposort();

        for (int i = 1; i <= n - 1; i++)
        {
            printf("%d ", topo[i]);
        }
        printf("%d\n", topo[n]);
    }

    return 0;
}