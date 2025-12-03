// learn from lrj
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 200 + 5;
int vis[maxn][maxn];
int cap[3];    // cap[1] 第 i 个壶能装的最大水量
int ans[maxn]; // ans[x] 表示达到水量 x 的最小代价

struct Node
{
    int v[3]; // 3 个水量
    int dist; // 达到此状态的总代价（倒水量）
    bool operator<(const Node &rhs) const { return dist > rhs.dist; }
};

// 记录当前状态 u 中所有壶的水量所对应的最小代价 dist。
void update_ans(const Node &u)
{
    for (int i = 0; i < 3; i++)
    {
        int d = u.v[i];
        if (ans[d] < 0 || u.dist < ans[d])
        {
            ans[d] = u.dist;
        }
    }
}

void solve(int a, int b, int c, int d)
{
    cap[0] = a;
    cap[1] = b;
    cap[2] = c;
    memset(vis, 0, sizeof(vis));
    memset(ans, -1, sizeof(ans));
    priority_queue<Node> q;
    Node start;
    start.dist = 0;
    start.v[0] = 0;
    start.v[1] = 0;
    start.v[2] = c;
    q.push(start);
    vis[0][0] = 1;

    while (!q.empty())
    {
        Node u = q.top();
        q.pop();
        update_ans(u);
        if (ans[d] >= 0)
        {
            break;
        }
        // 从壶 i 往壶 j 倒水
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i != j)
                {
                    if (u.v[i] == 0 || u.v[j] == cap[j]) // i 空或 j 满, 跳过
                    {
                        continue;
                    }
                    int amount = min(cap[j], u.v[i] + u.v[j]) - u.v[j];
                    Node u2;
                    memcpy(&u2, &u, sizeof(u));
                    u2.dist = u.dist + amount;
                    u2.v[i] -= amount;
                    u2.v[j] += amount;
                    if (!vis[u2.v[0]][u2.v[1]])
                    {
                        vis[u2.v[0]][u2.v[1]] = 1;
                        q.push(u2);
                    }
                }
            }
        }
    }
    while (d >= 0)
    {
        if (ans[d] >= 0)
        {
            printf("%d %d\n", ans[d], d);
            return;
        }
        d--;
    }
}

int main()
{
    int T, a, b, c, d;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        solve(a, b, c, d);
    }
    return 0;
}