// deepseek 教的，使用了 heap_pos 优化
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
int heap[maxn * maxk];     // 堆数组，存储节点编号
int heap_pos[maxn * maxk]; // 记录每个节点在堆中的位置
int heap_size = 0;         // 堆大小

struct Edge
{
    int to, next, cost;   // 这条边指向哪个节点，同一个起点 u 的下一条边索引，cost
} edges[maxn * maxk * 4]; // 开大一点，因为每条原始输入边，在分层层内、层间都会多产生边

void add(int u, int v, int cost)
{
    edges[++tot] = Edge{v, head[u], cost};
    head[u] = tot;
}

// 堆操作函数
void swap_heap(int i, int j)
{
    swap(heap[i], heap[j]);
    swap(heap_pos[heap[i]], heap_pos[heap[j]]);
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
    heap_pos[node] = heap_size;
    heap_up(heap_size);
}

int heap_front()
{
    return heap[1];
}

void heap_pop()
{
    swap_heap(1, heap_size);
    heap_pos[heap[heap_size]] = 0;
    heap_size--;
    heap_down(1);
}

bool heap_empty()
{
    return heap_size == 0;
}

void dijkstra()
{
    // 初始化
    for (int i = 0; i <= n * (k + 1); i++)
    {
        dis[i] = INT_MAX;
        vis[i] = false;
        heap_pos[i] = 0;
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

        // 遍历所有邻居
        for (int i = head[u]; i; i = edges[i].next)
        {
            int v = edges[i].to;
            int new_cost = dis[u] + edges[i].cost;
            if (new_cost < dis[v])
            {
                dis[v] = new_cost;
                if (heap_pos[v] == 0) // 节点不在堆中，插入
                {
                    heap_push(v);
                }
                else // 节点已在堆中，更新位置
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
    cin >> s >> t;

    // 构建分层图
    for (int i = 1; i <= m; i++)
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