// TLE
// UVa12171
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <tuple> //必须加上这一行
using namespace std;
const int maxn = 500 + 5;
const int H = 501;
int T, n;
int x0, y0, z0, x1, y1, z1, x, y, z;
bool occupied[maxn][maxn][maxn];
bool visited_air[maxn][maxn][maxn];

// direction
int dirx[6] = {1, -1, 0, 0, 0, 0};
int diry[6] = {0, 0, 1, -1, 0, 0};
int dirz[6] = {0, 0, 0, 0, 1, -1};

bool inRange(int x, int y, int z)
{
    if (x < 0 || x > H || y < 0 || y > H || z < 0 || z > H)
    {
        return false;
    }
    else
        return true;
}

void bfs(int &area, int &volume)
{
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    visited_air[0][0][0] = true;
    while (!q.empty())
    {
        int x, y, z;
        tie(x, y, z) = q.front();
        q.pop();

        for (int d = 0; d < 6; d++)
        {
            int nx = x + dirx[d], ny = y + diry[d], nz = z + dirz[d];
            if (!inRange(nx, ny, nz))
            {
                continue;
            }

            if (occupied[nx][ny][nz])
            {
                area++; // 这个面是外部空气接触到雕塑的表面
            }
            else if (visited_air[nx][ny][nz] == false)
            {
                visited_air[nx][ny][nz] = true;
                q.push({nx, ny, nz});
            }
        }
    }

    // calculate volume
    for (int i = 0; i <= H; i++)
    {
        for (int j = 0; j <= H; j++)
        {
            for (int k = 0; k <= H; k++)
            {
                if (occupied[i][j][k] || visited_air[i][j][k] == false)
                {
                    volume++;
                }
            }
        }
    }
    return;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        memset(occupied, false, sizeof(occupied));
        memset(visited_air, false, sizeof(visited_air));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d%d%d", &x0, &y0, &z0, &x, &y, &z);
            x1 = x0 + x - 1;
            y1 = y0 + y - 1;
            z1 = z0 + z - 1;
            // 标记 occupied
            for (int i = x0; i <= x1; i++)
            {
                for (int j = y0; j <= y1; j++)
                {
                    for (int k = z0; k <= z1; k++)
                    {
                        occupied[i][j][k] = true;
                    }
                }
            }
        }

        // floodfill

        int volume = 0;
        int area = 0;
        bfs(area, volume);
        printf("%d %d\n", area, volume);
    }
    return 0;
}