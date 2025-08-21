#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define ll long long
const ll maxn = 5e5 + 10;
const ll inf = 0x7fffffff;
ll n, m, start, tot;                             // 节点数、边数、起点、边计数器
ll heap[maxn], head[maxn], dis[maxn], idx[maxn]; // 手动堆、邻接表头、距离、节点在堆中的索引

struct node
{
    ll ptr, nxt, dis; // ptr:下条边索引, nxt:目标节点, dis:边权重
} edges[maxn << 1];   // 边数组

void add(ll u, ll v, ll w) // 添加边
{
    edges[++tot] = node({head[u], v, w});
    head[u] = tot;
}

void up(ll x) // 上浮操作，x 是堆中的位置
{
    for (ll i = x, j = x >> 1; j; i = j, j >>= 1)
    {
        if (dis[heap[i]] < dis[heap[j]])
        {
            swap(heap[i], heap[j]);
            swap(idx[heap[i]], idx[heap[j]]);
        }
        else
            break;
    }
    return;
}

void push(ll x)
{
    heap[++heap[0]] = x;
    idx[x] = heap[0];
    up(heap[0]);
}

void pop() // 下沉操作
{
    idx[heap[1]] = 0;
    idx[heap[heap[0]]] = 1;
    heap[1] = heap[heap[0]--];
    for (ll i = 1, j = 2; j <= heap[0]; i = j, j <<= 1)
    {
        if (j < heap[0] && dis[heap[j + 1]] < dis[heap[j]])
            j++;
        if (dis[heap[i]] > dis[heap[j]])
        {
            swap(heap[i], heap[j]);
            swap(idx[heap[i]], idx[heap[j]]);
        }
        else
            break;
    }
    return;
}

void dijkstra()
{
    for (ll i = 1; i <= n; i++)
    {
        dis[i] = inf;
    }
    dis[start] = 0;
    push(start);
    while (heap[0])
    {
        ll u = heap[1];                           // 取出堆顶元素（当前距离最小的节点）
        pop();                                    // 从堆中移除这个节点
        for (ll v = head[u]; v; v = edges[v].ptr) // 遍历节点u的所有出边
            if (dis[edges[v].nxt] > dis[u] + edges[v].dis)
            {
                dis[edges[v].nxt] = dis[u] + edges[v].dis;
                if (!idx[edges[v].nxt]) // 如果目标节点不在堆中
                {
                    push(edges[v].nxt); // 加入堆
                }
                else // 如果已经在堆中
                {
                    up(idx[edges[v].nxt]); // 更新其在堆中的位置（因为距离变小了）
                }
            }
    }
    return;
}

int main()
{
    cin >> n >> m >> start; // 节点数、边数、起点
    for (ll i = 1; i <= m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        add(u, v, w); // 构建邻接表（存图）
    }
    dijkstra();
    for (ll i = 1; i <= n; i++)
    {
        cout << dis[i] << (i == n ? "\n" : " ");
    }
    return 0;
}
