#include <cstdio>
#include <cstring>

using namespace std;
int map[7][8];
bool vis[7][8]; // 格子是否被覆盖
int ans[7][8];  // 保存每个格子属于哪块骨牌编号
int id[10][10]; // 多米诺骨牌的编号
int used[30];   // 骨牌是否被用过

int cnt;
const int dr[] = {0, 1};
const int dc[] = {1, 0};

// init [1, 28] unique bones
void init()
{
    int bone = 1;
    for (int i = 0; i < 7; i++)
    {
        for (int j = i; j < 7; j++)
        {
            id[i][j] = id[j][i] = bone++;
        }
    }
}

bool checkVisit(int x) // 这一行是否存在没有访问过的格子
{
    for (int i = 0; i < 8; ++i)
    {
        if (vis[x][i] == false)
        {
            return true;
        }
    }
    return false;
}

bool validIndex(int x, int y)
{
    return x >= 0 && x <= 6 && y >= 0 && y <= 7;
}
void dfs(int x, int y, int cur)
{
    if (cur == 28)
    {
        // 找到一个完整解
        cnt++;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%4d", ans[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
        return;
    }
    if (x == 7) // 已经扫完整个棋盘, 但骨牌还没放满（cur < 28）, 剪枝
    {
        return;
    }
    if (y == 8) // 当前行已经扫描完
    {
        if (checkVisit(x))
        {
            return; // 这一行还有未覆盖的格子, 剪枝
        }
        dfs(x + 1, 0, cur);
        return;
    }
    if (vis[x][y])
    { // 如果当前位置 (x, y) 已经被覆盖, 直接扫描下一个位置
        dfs(x, y + 1, cur);
        return;
    }
    for (int i = 0; i < 2; ++i) // 向右或向下
    {
        int tx = x + dr[i];
        int ty = y + dc[i];

        if (!validIndex(tx, ty))
            continue;
        if (vis[tx][ty])
            continue;
        int bone = id[map[x][y]][map[tx][ty]];
        if (used[bone])
            continue; // 这张骨牌已经用过

        // 尝试放置这张骨牌
        used[bone] = true;
        vis[x][y] = vis[tx][ty] = true;
        ans[x][y] = ans[tx][ty] = bone;

        dfs(x, y + 1, cur + 1);

        // 回溯
        used[bone] = false;
        vis[x][y] = vis[tx][ty] = false;
        ans[x][y] = ans[tx][ty] = 0;
    }
}
int main()
{
    init();
    int kase = 0;
    while (true)
    {
        if (scanf("%d", &map[0][0]) != 1)
        {
            break;
        }
        // init
        cnt = 0;
        memset(vis, 0, sizeof(vis));
        memset(used, 0, sizeof(used));
        memset(ans, 0, sizeof(ans));
        // 读完这一组剩下的 55 个数
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (i == 0 && j == 0)
                {
                    continue;
                }
                scanf("%d", &map[i][j]);
            }
        }
        if (kase > 0)
        {
            printf("\n\n\n\n\n");
        }
        printf("Layout #%d:\n\n\n", ++kase);
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%4d", map[i][j]);
            }
            printf("\n");
        }
        printf("\nMaps resulting from layout #%d are:\n\n\n", kase);

        // 处理这一组棋盘
        dfs(0, 0, 0);
        printf("There are %d solution(s) for layout #%d.\n", cnt, kase);
    }

    return 0;
}