#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 20 + 5;

vector<int> adj[maxn];
int n;
int routes;
int path[maxn], vis[maxn];

bool check_connect() // 从 1 可以到目的地 n 吗
{
    queue<int> q;
    q.push(1);
    bool visited[maxn] = {false}; // 访问标记数组
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == n)
        {
            return true;
        }
        for (int v : adj[u])
        {
            if (visited[v] == false)
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}
void print(int cur)
{
    for (int i = 1; i < cur; ++i)
    {
        printf("%d ", path[i]);
    }
    printf("%d\n", path[cur]);
}
void dfs(int u, int cur) // cur: 当前路径长度
{
    if (u == n)
    {
        routes++;
        print(cur);
        return;
    }
    for (int v : adj[u])
    {
        if (vis[v] == false)
        {
            vis[v] = true;
            path[cur + 1] = v;
            dfs(v, cur + 1);
            vis[v] = 0;
        }
    }
}

int main()
{
    int kase = 0;

    while (scanf("%d", &n) != EOF)
    {
        // init
        for (int i = 0; i < maxn; i++)
        {
            adj[i].clear();
        }
        // read
        int x, y;
        while (scanf("%d %d", &x, &y) && x)
        {
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        for (int i = 0; i < maxn; i++)
        {
            if (adj[i].size() > 0)
            {
                sort(adj[i].begin(), adj[i].end());
            }
        }
        printf("CASE %d:\n", ++kase);
        routes = 0;

        if (check_connect())
        {
            memset(vis, 0, sizeof(vis));
            vis[1] = 1;
            path[1] = 1;
            dfs(1, 1);
        }
        printf("There are %d routes from the firestation to streetcorner %d.\n", routes, n);
    }

    return 0;
}