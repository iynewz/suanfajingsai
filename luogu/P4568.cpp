// 只能拿 80 分，有测试点没过
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int maxn = 100010;
const int maxk = 11;

int n, m, k;
int s, t;
int tot = 0;
int head[maxn * maxk];
int dis[maxn * maxk];
bool vis[maxn * maxk];

// 手写堆
int heap[maxn * maxk * 2]; // 需要更大的堆空间，因为可能有重复插入
int heap_size = 0;         // 堆大小

struct Edge
{
    int to, next, cost;
} edges[maxn * maxk * 4];

void add(int u, int v, int cost)
{
    edges[++tot] = Edge{v, head[u], cost};
    head[u] = tot;
}

void swap_heap(int i, int j)
{
    swap(heap[i], heap[j]);
}

void heap_up(int pos)
{
    while (pos > 1)
    {
        int parent = pos / 2;
        if (dis[heap[pos]] < dis[heap[parent]])
        {
            swap_heap(pos, parent);
            pos = parent;
        }
        else
        {
            break;
        }
    }
}

void heap_down(int pos)
{
    while (pos * 2 <= heap_size)
    {
        int left = pos * 2;
        int right = pos * 2 + 1;
        int min_child = left;

        if (right <= heap_size && dis[heap[right]] < dis[heap[left]])
        {
            min_child = right;
        }

        if (dis[heap[min_child]] < dis[heap[pos]])
        {
            swap_heap(pos, min_child);
            pos = min_child;
        }
        else
        {
            break;
        }
    }
}

void heap_push(int node)
{
    heap[++heap_size] = node;
    heap_up(heap_size);
}

int heap_front()
{
    return heap[1];
}

void heap_pop()
{
    swap_heap(1, heap_size);
    heap_size--;
    heap_down(1);
}

bool heap_empty()
{
    return heap_size == 0;
}

void dijkstra()
{
    for (int i = 0; i <= n * (k + 1); i++) // 初始化
    {
        dis[i] = INT_MAX;
        vis[i] = false;
    }
    dis[s] = 0;
    heap_size = 0;
    heap_push(s);

    while (!heap_empty())
    {
        int u = heap_front();
        heap_pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;

        // 遍历 u 的所有邻居
        for (int i = head[u]; i; i = edges[i].next)
        {
            int v = edges[i].to; // 邻节点
            int cost = edges[i].cost;

            if (dis[u] + cost < dis[v])
            {
                dis[v] = dis[u] + cost;
                heap_push(v); // 直接插入堆中，不管是否已经在堆中，可能是这里优化
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    cin >> s >> t;
    for (int i = 1; i <= m; i++) // 构建分层图
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c); // 无向图
        for (int j = 1; j <= k; j++)
        {
            add(a + (j - 1) * n, b + j * n, 0);
            add(b + (j - 1) * n, a + j * n, 0);
            add(a + j * n, b + j * n, c);
            add(b + j * n, a + j * n, c); // 无向图
        }
    }

    dijkstra();

    // 在所有层的终点中找最小值
    int ans = INT_MAX;
    for (int i = 0; i <= k; i++)
    {
        ans = min(ans, dis[t + i * n]);
    }
    cout << ans << endl;

    return 0;
}