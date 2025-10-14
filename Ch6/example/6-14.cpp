#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int r, c, dir;
    Node(int r = 0, int c = 0, int dir = 0) : r(r), c(c), dir(dir) {}
};

const int maxn = 10;
int d[maxn][maxn][4];            // 到每个状态的最短距离
bool has_edge[maxn][maxn][4][3]; // has_edge[r][c][dirs][turns] 在每个位置、每个朝向下，有哪些合法的移动选项
Node p[maxn][maxn][4];
const char *dirs = "NESW"; // 0-N; 1-E; 2-S; 3-W
const char *turns = "FLR"; // 0-front; 1-left; 2-right
int dir_id(char c) { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }

int r0, c0, dir;
int r1, c1; // 实际起点
int r2, c2; // 终点

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

bool inside_grid(int r, int c)
{
    return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

Node walk(const Node &u, int turn)
{
    int dir = u.dir;
    if (turn == 1) // turn left
    {
        dir = (dir + 3) % 4;
    }
    else if (turn == 2) // turn right
    {
        dir = (dir + 1) % 4;
    }
    return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

void print_ans(Node u)
{
    // 从目标结点逆序追溯到初始结点
    vector<Node> nodes;
    for (;;)
    {
        nodes.push_back(u);
        if (d[u.r][u.c][u.dir] == 0)
            break;
        u = p[u.r][u.c][u.dir];
    }
    nodes.push_back(Node(r0, c0, dir));

    int cnt = 0;
    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        if (cnt % 10 == 0)
            printf(" ");
        printf(" (%d,%d)", nodes[i].r, nodes[i].c);
        if (++cnt % 10 == 0)
            printf("\n");
    }
    if (nodes.size() % 10 != 0)
        printf("\n");
}

bool read_case()
{
    char s[99], s2[99];
    if (scanf("%s%d%d%s%d%d", s, &r0, &c0, s2, &r2, &c2) != 6)
    {
        return false;
    }
    printf("%s\n", s);

    dir = dir_id(s2[0]);
    r1 = r0 + dr[dir];
    c1 = c0 + dc[dir];

    memset(has_edge, false, sizeof(has_edge));
    for (;;)
    {
        int r, c;
        scanf("%d", &r);
        if (r == 0)
            break;
        scanf("%d", &c);
        while (scanf("%s", s) == 1 && s[0] != '*')
        {
            for (int i = 1; i < strlen(s); i++)
                has_edge[r][c][dir_id(s[0])][turn_id(s[i])] = true;
        }
    }
    return true;
}

void solve()
{
    queue<Node> q;
    memset(d, -1, sizeof(d));
    Node start(r1, c1, dir);
    d[start.r][start.c][start.dir] = 0;
    q.push(start);
    while (!q.empty())
    {
        Node u = q.front();
        q.pop();
        if (u.c == c2 && u.r == r2)
        {
            print_ans(u);
            return;
        }
        for (int i = 0; i < 3; i++)
        {
            Node v = walk(u, i);
            if (has_edge[u.r][u.c][u.dir][i] && inside_grid(v.r, v.c) && d[v.r][v.c][v.dir] == -1)
            {
                d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
                p[v.r][v.c][v.dir] = u;
                q.push(v);
            }
        }
    }
    printf("  No Solution Possible\n");
}

int main()
{
    while (read_case())
    {
        solve();
    }
    return 0;
}