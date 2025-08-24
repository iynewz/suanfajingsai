#include <iostream>
#include <queue>
#include <climits>

using namespace std;

const int maxn = 10000 + 5;
const int maxk = 100 + 5;
const int INF = INT_MAX;

int n, m, k;
int dis[maxn][maxk]; // d[i][j] 是指到达点 i, 且到达时间 mod k = j 的最早实际到达时间

int head[maxn * maxk];
int tot = 0;

struct Edge
{
    int to, next, open_time;
} edges[maxn * maxk * 4];

void add(int u, int v, int open_time)
{
    tot++;
    edges[tot] = Edge({v, head[u], open_time});
    head[u] = tot;
}

struct State
{
    int node;       // 当前节点
    int mod;        // 时间模k的余数
    long long time; // 实际到达时间
    bool operator>(const State &other) const
    {
        return time > other.time;
    }
};

void dijkstra()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            dis[i][j] = INF;
        }
    }
    dis[1][0] = 0;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({1, 0, 0});

    while (!pq.empty())
    {
        State curr = pq.top();
        pq.pop();
        if (curr.time != dis[curr.node][curr.mod]) // 如果当前状态不是最短的，跳过
        {
            continue;
        }
        // 遍历当前节点所有邻居
        for (int i = head[curr.node]; i; i = edges[i].next)
        {
            int v = edges[i].to;
            int a = edges[i].open_time;
            long long next_time = curr.time;
            // 如果当前时间小于边的开放时间，需要等待
            if (curr.time < a)
            {
                // 计算需要等待的完整 k 周期数
                long long wait_cycles = (a - curr.time + k - 1) / k;
                next_time += wait_cycles * k;
            }
            next_time += 1; // 通过这条边需要 1 单位时间
            int next_mod = next_time % k;
            if (next_time < dis[v][next_mod]) // 如果找到更短的路径，更新
            {
                dis[v][next_mod] = next_time;
                pq.push({v, next_mod, next_time});
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int u, v, a;
        cin >> u >> v >> a;
        add(u, v, a); // 存图
    }
    dijkstra();

    if (dis[n][0] == INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dis[n][0] << endl;
    }
    return 0;
}