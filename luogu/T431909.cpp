// BFS
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1000000 + 5;       // 最大顶点数
const int MAXM = (1000000 + 5) * 2; // 最大边数

struct Edge
{
    int v;    // 边的终点
    int next; // 下一条边的索引
    int w;    // 边的权值
} edges[MAXM];

int head[MAXN]; // head[u] 表示顶点u的第一条边的索引
int L = 1;      // 当前存的边，记得初始化
int visit[MAXN];
queue<int> q;

// 链式前向星存图
void add_edge(int u, int v, int w = 0)
{
    edges[L].v = v;
    edges[L].w = w;
    edges[L].next = head[u];
    head[u] = L;
    L++;
}

void bfs()
{
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (int p = head[u]; p != 0; p = edges[p].next)
        { // 遍历邻接点
            int v = edges[p].v;
            if (!visit[v])
            {
                visit[v] = true;
                q.push(v);
            }
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
        add_edge(v, u);
    }

    // 从结点 1 开始 BFS
    q.push(1);
    visit[1] = true;
    bfs();

    cout << endl;
    return 0;
}