#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
const int maxn = 100000 + 5;
const int maxm = 200000 + 5;

struct Edge
{
    int to;
    int w;
    int next;
};

Edge edges[maxm];
int head[maxn]; // head[u] = 第一条边编号
int tot;        // 边计数

int dist[maxn]; // 每个点到终点 n 的最短距离
bool visited[maxn];


void bfs(int start)
{
    memset(dist, -1, sizeof(dist));
    memset(visited, false, sizeof(visited));

    queue<int> q;
    q.push(start);
    dist[start] = 0;
    visited[start] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != 0; i = edges[i].next)
        {
            int v = edges[i].to;
            if (!visited[v])
            {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return;
}

int main()
{
    int n, m;
    int u, v, w;

    while (scanf("%d %d", &n, &m) == 2)
    {

        // init
        tot = 0;
        memset(head, 0, sizeof(head));

        for (int i = 0; i <= m; i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }

        bfs(n);

        for()
        // test: 输出每个点 i 到终点的距离
        for (int i = 1; i <= n; i++)
        {
            printf("dist[%d] = %d\n", i, dist[i]);
        }
    }

    return 0;
}