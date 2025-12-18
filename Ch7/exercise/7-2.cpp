#include <cstdio>
#include <cstring>
using namespace std;

#define LINENUMMAX 22
#define MAPSIZE 600
#define OFFSET 250

int maxEdge;

// 当前路径
int line[LINENUMMAX];

// 所有解
int totalNum;
int lineTotal[5000][LINENUMMAX];

// 地图：0 空，1 端点，2 线段/障碍
int map[MAPSIZE][MAPSIZE];

// 方向：1=e, 2=n, 3=s, 4=w
char num2str[5] = {0, 'e', 'n', 's', 'w'};
int dir[5][2] = {{0, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 0}};

// 左转 / 右转
int truns[5][2] = {
    {0, 0},
    {2, 3}, // e -> n,s
    {1, 4}, // n -> e,w
    {1, 4}, // s -> e,w
    {2, 3}  // w -> n,s
};

// 判断 (x,y) -> (xnew,ynew) 的线段上是否有阻碍
bool hasBlock(int d, int x, int y, int xnew, int ynew)
{
    if (d == 1) // e
    {
        for (int i = x + 1; i <= xnew; i++)
            if (map[i + OFFSET][y + OFFSET] == 2)
                return true;
    }
    if (d == 2) // n
    {
        for (int i = y + 1; i <= ynew; i++)
            if (map[x + OFFSET][i + OFFSET] == 2)
                return true;
    }
    if (d == 3) // s
    {
        for (int i = ynew; i < y; i++)
            if (map[x + OFFSET][i + OFFSET] == 2)
                return true;
    }
    if (d == 4) // w
    {
        for (int i = xnew; i < x; i++)
            if (map[i + OFFSET][y + OFFSET] == 2)
                return true;
    }
    return false;
}

void dfs(int step, int lastDir, int x, int y)
{
    if (x == 0 && y == 0 && step == maxEdge)
    {
        for (int i = 0; i < maxEdge; i++)
            lineTotal[totalNum][i] = line[i];
        totalNum++;
        return;
    }
    if (step >= maxEdge)
        return;

    map[x + OFFSET][y + OFFSET] = 1;

    for (int k = 0; k < 2; k++)
    {
        int nd = truns[lastDir][k];
        int nx = x + (step + 1) * dir[nd][0];
        int ny = y + (step + 1) * dir[nd][1];

        if (map[nx + OFFSET][ny + OFFSET])
            continue;
        if (hasBlock(nd, x, y, nx, ny))
            continue;

        line[step] = nd;
        dfs(step + 1, nd, nx, ny);
    }

    map[x + OFFSET][y + OFFSET] = 0;
}

// 初始四个方向
void solve()
{
    for (int i = 1; i <= 4; i++)
    {
        int x = dir[i][0];
        int y = dir[i][1];
        if (map[x + OFFSET][y + OFFSET] == 0)
        {
            line[0] = i;
            dfs(1, i, x, y);
        }
    }
}

int main()
{
    int city;
    scanf("%d", &city);
    while (city--)
    {
        memset(map, 0, sizeof(map));
        memset(lineTotal, 0, sizeof(lineTotal));
        memset(line, 0, sizeof(line));
        totalNum = 0;

        int blockNum, x, y;
        scanf("%d%d", &maxEdge, &blockNum);
        for (int i = 0; i < blockNum; i++)
        {
            scanf("%d%d", &x, &y);
            map[x + OFFSET][y + OFFSET] = 2; // 标记障碍
        }

        solve();

        for (int i = 0; i < totalNum; i++)
        {
            for (int j = 0; j < maxEdge; j++)
                printf("%c", num2str[lineTotal[i][j]]);
            putchar('\n');
        }
        printf("Found %d golygon(s).\n\n", totalNum);
    }
    return 0;
}
