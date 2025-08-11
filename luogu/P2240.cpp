// greedy
#include <iostream>
#include <algorithm>

using namespace std;

int N, T;     // N 堆金币，包承重 T
int capacity; // 背包剩余容量

int weight[100 + 5];
int value[100 + 5];

struct Coin
{
    int m; // 总重量
    int v; // 总价值
} a[110];

bool cmp(Coin a, Coin b)
{
    return a.v * b.m > b.v * a.m; // better than  a.v / a.m > b.v / b.m;
}

int main()
{
    float ans = 0;
    cin >> N >> T;
    capacity = T;

    for (int i = 0; i < N; i++)
    {
        cin >> a[i].m >> a[i].v;
    }
    sort(a, a + N, cmp);
    int i;
    for (i = 0; i < N; i++)
    {
        if (a[i].m > capacity)
        {
            break;
        }
        capacity -= a[i].m;
        ans += a[i].v;
    }
    if (i < N)
    {
        ans += 1.0 * capacity / a[i].m * a[i].v;
    }
    printf("%.2lf\n", ans);
    return 0;
}