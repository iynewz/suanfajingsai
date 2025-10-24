#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 100000 + 5;
const int maxm = 200000 + 5;

struct Edge
{
    int to;
    int w;
    int next;
};

Edge edges[maxm * 2]; // 忘记开 2 倍了
int head[maxn];       // head[u] = 第一条边编号
int tot;              // 边计数

int dist[maxn]; // 每个点到终点 n 的最短距离
bool visited[maxn];

void add(int u, int v, int w)
{
    tot++;
    edges[tot] = Edge{v, w, head[u]};
    head[u] = tot;
}

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
void bfs_color(int start)
{
    memset(visited, false, sizeof(visited));

    queue<int> q; // 这一层可能的起点
    q.push(start);
    visited[start] = true;
    int print_flag = 0;
    while (!q.empty())
    {
        int size = q.size();
        int min_color = 1e9;
        vector<pair<int, int>> candidates; // 所有下一层 点 和 连边颜色

        for (int i = 0; i < size; i++) // 遍历这一层可能的起点
        {
            int u = q.front(); // 一个起点 u
            q.pop();

            for (int j = head[u]; j != 0; j = edges[j].next) // 找边颜色最小的起点
            {
                int v = edges[j].to;
                int w = edges[j].w;          // u 到 v 边的颜色
                if (dist[v] - dist[u] == -1) // v 作为下一个节点，可以构成最短路; 第一次写成了 1， 应为 -1
                {
                    if (w <= min_color)
                    {
                        min_color = w;
                    }
                    candidates.push_back({v, w});
                }
            }
        }
        if (candidates.empty())
        {
            break;
        }

        for (auto item : candidates)
        {
            if (item.second == min_color && visited[item.first] == false)
            {
                visited[item.first] = true;
                q.push(item.first); // 最优解才可以作为下一层的起点，加入队列
            }
        }
        print_flag == 0 ? printf("%d", min_color) : printf(" %d", min_color);
        print_flag = 1;
    }
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

        for (int i = 1; i <= m; i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }

        bfs(n);
        printf("%d\n", dist[1]); // 输出起点到终点的最小距离
        bfs_color(1);
        printf("\n");
    }

    return 0;
}