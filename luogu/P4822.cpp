#include <iostream>
#include <climits>
using namespace std;

const int maxn = 50 + 5; // runtime error

const int maxk = 50 + 5;
const int maxm = 1000 + 5;
int n, m, k;

int head[maxn * maxk];
int dis[maxn * maxk]; // 起点 到 i 点最短距离
bool vis[maxn * maxk];
int tot = 0;

int heap[maxn * maxk * 2];
int heap_pos[maxn * maxk * 2];
int heap_size;

struct Edge
{
    int to, next, weight;
} edges[maxm * maxk * 4];

void add(int u, int v, int w)
{
    tot++;
    edges[tot] = Edge{v, head[u], w};
    head[u] = tot;
}

void swap_heap(int a, int b)
{
    heap_pos[heap[a]] = b;
    heap_pos[heap[b]] = a;
    swap(heap[a], heap[b]);
}

int heap_front()
{
    return heap[1];
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

void heap_pop()
{
    swap_heap(1, heap_size);
    heap_pos[heap[heap_size]] = 0;
    heap_size--;
    heap_down(1);
}

void heap_push(int node)
{
    heap_size++;
    heap[heap_size] = node;
    heap_pos[node] = heap_size;
    heap_up(heap_size);
}

void dijkstra()
{
    for (int i = 1; i <= n * (k + 1); i++)
    {
        dis[i] = INT_MAX;
        vis[i] = false;
    }
    dis[1] = 0;
    heap_size = 0;
    heap_push(1);
    while (heap_size != 0)
    {
        int u = heap_front();
        heap_pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;
        for (int i = head[u]; i; i = edges[i].next)
        {
            int v = edges[i].to;
            if (dis[u] + edges[i].weight < dis[v])
            {
                dis[v] = dis[u] + edges[i].weight; // 成功松弛一条边，第一次写，漏了
                if (heap_pos[v] == 0)              // 节点不在堆中，插入
                {
                    heap_push(v);
                }
                else
                {
                    heap_up(heap_pos[v]);
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
        // 同层之间的边（不使用优惠券）注意一共是 k + 1 层
        for (int j = 0; j <= k; j++)
        {
            add(u + j * n, v + j * n, w);
            add(v + j * n, u + j * n, w);
        }

        // 跨层的边（使用优惠券，半价）
        for (int j = 1; j <= k; j++)
        {
            add(u + (j - 1) * n, v + j * n, w / 2);
            add(v + (j - 1) * n, u + j * n, w / 2);
        }
    }
    dijkstra();
    int min = INT_MAX;
    for (int i = 0; i <= k; i++)
    {
        int tmp = dis[i * n + n];
        if (tmp < min)
        {
            min = tmp;
        }
    }
    cout << min << endl;
    return 0;
}
