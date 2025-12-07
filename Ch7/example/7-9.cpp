#include <cstdio>
#include <cstring>
#include <queue>
#include <cctype>
using namespace std;

const int maxn = 256;
const int maxs = 20;
const int dx[] = {-1, 1, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0};
int start[3], target[3]; // ghost start and target

// struct State
// {
//     int a[3]; // positions of ghosts
// };
void test_print(char raw_pic[20][20], int h)
{
    for (int i = 0; i < h; i++)
    {
        printf("[%s]\n", raw_pic[i]); // 用 [] 好区分空格
    }
}
int d[maxn][maxn][maxn]; // distance from starting state

inline int ID(int a, int b, int c)
{
    return (a << 16) | (b << 8) | c;
}

int deg[maxn], G[maxn][5];

inline bool conflict(int a, int b, int a2, int b2)
{
    return a2 == b2 || (a2 == b && b2 == a); // 移动后是同一个格子，不行！互换位置，不行！
}
int bfs()
{
    queue<int> q;
    memset(d, -1, sizeof(d));
    q.push(ID(start[0], start[1], start[2]));
    d[start[0]][start[1]][start[2]] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int a = (u >> 16) & 0xff, b = (u >> 8) & 0xff, c = u & 0xff; // 还原 cnt
        if (a == target[0] && b == target[1] && c == target[2])
        {
            return d[a][b][c];
        }
        for (int i = 0; i < deg[a]; i++)
        {
            int a2 = G[a][i];
            for (int j = 0; j < deg[b]; j++)
            {
                int b2 = G[b][j];
                if (conflict(a, b, a2, b2))
                    continue;
                for (int k = 0; k < deg[c]; k++)
                {
                    int c2 = G[c][k];
                    if (conflict(a, c, a2, c2))
                        continue;
                    if (conflict(b, c, b2, c2))
                        continue;
                    if (d[a2][b2][c2] != -1)
                        continue;
                    d[a2][b2][c2] = d[a][b][c] + 1;
                    q.push(ID(a2, b2, c2));
                }
            }
        }
    }
    return -1;
}
int main()
{
    int w, h, n; // h 行 w 列
    while (scanf("%d%d%d\n", &w, &h, &n) == 3 && n)
    {
        char raw_pic[20][20];
        for (int i = 0; i < h; i++)
        {
            fgets(raw_pic[i], 20, stdin);
            int L = strlen(raw_pic[i]);
            if (L > 0 && raw_pic[i][L - 1] == '\n') // remove ending '/n'
            {
                raw_pic[i][L - 1] = '\0';
            }
        }
        // test_print(raw_pic, h);
        //
        int cnt = 0;          // 统计所有非墙（#）的格子数量 cnt
        int x[maxn], y[maxn]; // 编号 cnt 对应的坐标是(i, j): x[cnt] = i; y[cnt] = j;
        int id[maxs][maxs];   // id[i][j] = cnt
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                char curr = raw_pic[i][j];
                if (curr != '#')
                {

                    x[cnt] = i;
                    y[cnt] = j;
                    id[i][j] = cnt;
                    if (islower(curr))
                    {
                        start[curr - 'a'] = cnt;
                    }
                    else if (isupper(curr))
                    {
                        target[curr - 'A'] = cnt; // 第一次错写成 a 了
                    }
                    cnt++;
                }
            }
        }
        for (int i = 0; i < cnt; i++)
        {
            deg[i] = 0; // 编号 i 这个格子有多少个可走的邻居。
            for (int j = 0; j < 5; j++)
            {
                int newx = x[i] + dx[j];
                int newy = y[i] + dy[j];
                if (raw_pic[newx][newy] != '#')
                {
                    G[i][deg[i]++] = id[newx][newy];
                }
            }
        }
        // Add fake ghost
        if (n <= 2)
        {
            deg[cnt] = 1;
            G[cnt][0] = cnt;
            start[2] = target[2] = cnt++;
        }
        if (n <= 1)
        {
            deg[cnt] = 1;
            G[cnt][0] = cnt;
            start[1] = target[1] = cnt++;
        }
        printf("%d\n", bfs());
    }
    return 0;
}