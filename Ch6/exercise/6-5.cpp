#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int maxn = 20 + 5;
int dist[maxn][maxn][maxn]; // dist[x][y][k] 位于 (x,y) 且连续穿过 k 个障碍时的，距离起点最短距离
int grid[maxn][maxn];

int direction[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

struct Node
{
    int x, y, k;
    Node(int x = 0, int y = 0, int k = 0) : x(x), y(y), k(k) {}
};

int m, n, k;
bool inside_grid(int x, int y)
{
    return x >= 1 && x <= m && y >= 1 && y <= n;
};
int solve()
{
    queue<Node> q;
    Node start(1, 1, 0);
    q.push(start);
    dist[1][1][0] = 0;

    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();
        int curr_d = dist[cur.x][cur.y][cur.k];
        if (cur.x == m && cur.y == n)
        {
            return curr_d;
        }
        for (int i = 0; i < 4; i++)
        {
            int new_x = cur.x + direction[i][0];
            int new_y = cur.y + direction[i][1];
            if (!inside_grid(new_x, new_y))
            {
                continue;
            }
            if (grid[new_x][new_y] == 1)
            {
                if (cur.k + 1 <= k && dist[new_x][new_y][cur.k + 1] == -1)
                {
                    dist[new_x][new_y][cur.k + 1] = curr_d + 1;
                    q.push(Node(new_x, new_y, cur.k + 1));
                }
            }
            else if (grid[new_x][new_y] == 0)
            {
                if (dist[new_x][new_y][0] == -1)
                {
                    dist[new_x][new_y][0] = curr_d + 1;
                    q.push(Node(new_x, new_y, 0));
                }
            }
        }
    }
    return -1;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d", &m, &n, &k);
        memset(dist, -1, sizeof(dist));

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &grid[i][j]);
            }
        }
        int steps = solve();
        printf("%d\n", steps);
    }
    return 0;
}