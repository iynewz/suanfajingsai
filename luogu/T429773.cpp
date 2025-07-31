// DFS
#include <iostream>
using namespace std;
const int MAXN = 1000000 + 5; // 最大顶点数
const int MAXM = 1000000 + 5; // 最大边数

struct Edge
{
    int v;    // 边的终点
    int next; // 下一条边的索引
    int w;    // 边的权值
} edges[MAXM];

int head[MAXN]; // head[u] 表示顶点u的第一条边的索引
int L = 1;      // 当前存的边，记得初始化
int visit[MAXN];

// 链式前向星存图
void add_edge(int u, int v, int w = 0)
{
    edges[L].v = v;
    edges[L].w = w;
    edges[L].next = head[u];
    head[u] = L;
    L++;
}

void dfs(int i)
{
    cout << i << " ";
    for (int p = head[i]; p; p = edges[p].next) // 遍历顶点 u 的所有邻接边
    {
        int v = edges[p].v;
        // int w = edges[p].w;
        if (!visit[v])
        {
            visit[v] = true;
            dfs(v);
        }
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    int u, v;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        add_edge(u, v);
    }

    for (int i = 1; i <= N; i++)
    {
        if (!visit[i])
        {
            visit[i] = true;
            dfs(i);
        }
    }
    cout << endl;
    return 0;
}