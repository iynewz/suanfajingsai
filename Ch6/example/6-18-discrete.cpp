// segmentation fault
// UVa12171
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <tuple> //必须加上这一行
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
const int maxk = 200 + 10;
int T, n;

bool occupied[maxk][maxk][maxk];
bool visited_air[maxk][maxk][maxk];
vector<int> xs, ys, zs; // xs 记录了有多少个本质不同的 x 坐标点

// direction
int dirx[6] = {1, -1, 0, 0, 0, 0};
int diry[6] = {0, 0, 1, -1, 0, 0};
int dirz[6] = {0, 0, 0, 0, 1, -1};

int size_x, size_y, size_z; // 离散后有几个本质不同的点

bool inRange(int x, int y, int z)
{
    return (0 <= x && x < size_x &&
            0 <= y && y < size_y &&
            0 <= z && z < size_z);
}

int calc_area(int x, int y, int z, int d)
{ // 还原原始坐标再计算表面积
    int dx = xs[x + 1] - xs[x];
    int dy = ys[y + 1] - ys[y];
    int dz = zs[z + 1] - zs[z];
    switch (d)
    {
    case 0:             // +x
    case 1:             // -x
        return dy * dz; //
    case 2:             // +y
    case 3:             // -y
        return dx * dz;
    case 4: // +z
    case 5: // -z
        return dx * dy;
    default:
        return 0;
    }
}

int calc_volume(int i, int j, int k)
{
    int dx = xs[i + 1] - xs[i];
    int dy = ys[j + 1] - ys[j];
    int dz = zs[k + 1] - zs[k];
    return dx * dy * dz;
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
                area += calc_area(nx, ny, nz, d); // 这个面是外部空气 - 雕塑的表面 接触面
            }
            else if (visited_air[nx][ny][nz] == false)
            {
                visited_air[nx][ny][nz] = true;
                q.push({nx, ny, nz});
            }
        }
    }

    // calculate volume
    for (int i = 0; i < size_x - 1; i++)
    {
        for (int j = 0; j < size_y - 1; j++)
        {
            for (int k = 0; k < size_z - 1; k++)
            {
                if (visited_air[i][j][k] == false)
                {
                    volume += calc_volume(i, j, k); // 类比 calc_area
                }
            }
        }
    }
    return;
}

int getIndex(vector<int> &v, int val)
{
    return lower_bound(v.begin(), v.end(), val) - v.begin();
}

void compress(vector<int> &v)
{
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end()); // v[i] 就代表第 i 段的“实际坐标值”
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
        xs.clear();
        ys.clear();
        zs.clear();
        int x0, y0, z0, x1, y1, z1, x, y, z;
        vector<array<int, 6>> boxes;

        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d%d%d", &x0, &y0, &z0, &x, &y, &z); // 读取原始长方体
            x1 = x0 + x;
            y1 = y0 + y;
            z1 = z0 + z;
            boxes.push_back({x0, y0, z0, x1, y1, z1});
            xs.push_back(x0);
            xs.push_back(x1);
            ys.push_back(y0);
            ys.push_back(y1);
            zs.push_back(z0);
            zs.push_back(z1);
        }

        compress(xs);
        compress(ys);
        compress(zs);

        xs.insert(xs.begin(), xs.front() - 1);
        ys.insert(ys.begin(), ys.front() - 1);
        zs.insert(zs.begin(), zs.front() - 1);
        xs.push_back(xs.back() + 1);
        ys.push_back(ys.back() + 1);
        zs.push_back(zs.back() + 1);

        size_x = xs.size() - 1;
        size_y = ys.size() - 1;
        size_z = zs.size() - 1;

        for (auto &b : boxes)
        {
            int x0 = b[0], y0 = b[1], z0 = b[2];
            int x1 = b[3], y1 = b[4], z1 = b[5];

            int ix0 = getIndex(xs, x0);
            int ix1 = getIndex(xs, x1);
            int iy0 = getIndex(ys, y0);
            int iy1 = getIndex(ys, y1);
            int iz0 = getIndex(zs, z0);
            int iz1 = getIndex(zs, z1);

            for (int i = ix0; i < ix1; ++i)
                for (int j = iy0; j < iy1; ++j)
                    for (int k = iz0; k < iz1; ++k)
                        occupied[i][j][k] = true;
        }
    }

    int volume = 0;
    int area = 0;
    bfs(area, volume);
    printf("%d %d\n", area, volume);

    return 0;
}