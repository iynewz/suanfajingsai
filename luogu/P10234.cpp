#include <iostream>
#include <queue>
using namespace std;

int T, n, m;
int grid[2005][2005];
bool visit[2005][2005];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
char dir2[4] = {'R', 'L', 'D', 'U'}; // right, left, down , up

char from1[2005][2005];
int from2[2005][2005][2]; // 每一个格子，从哪个格子来

struct Node
{
    int curx, cury;
    int step;                                         // 到达这个 node 需要的最短步数
    Node(int curx1 = 0, int cury1 = 0, int step1 = 0) // 构造函数
    {
        curx = curx1;
        cury = cury1;
        step = step1;
    }
};

void init()
{
    cin >> n >> m; // 行数和列数
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            char c;
            cin >> c;
            grid[i][j] = c - '0'; // create grid
            visit[i][j] = false;
            from1[i][j] = '\0';
            from2[i][j][0] = from2[i][j][1] = 0;
        }
    }
    return;
}

void printAns(int x, int y)
{
    if (x == 1 && y == 1)
    {
        return;
    }
    else
    {
        printAns(from2[x][y][0], from2[x][y][1]);
        cout << from1[x][y];
    }
}

void solve()
{
    queue<Node> Q;
    Q.push(Node(1, 1, 0)); // 左上的起始点
    visit[1][1] = true;
    while (!Q.empty())
    {
        Node f = Q.front();
        Q.pop();
        if (f.curx == n && f.cury == m) // 如果走到了右下终点
        {
            cout << f.step << endl;
            printAns(n, m);
            cout << endl;
            return;
        }
        for (int i = 0; i < 4; i++) // 遍历邻居节点
        {
            int new_x = f.curx + dir[i][0];
            int new_y = f.cury + dir[i][1];
            if (new_x < 1 || new_x > n || new_y < 1 || new_y > m)
            {
                continue;
            }

            if (visit[new_x][new_y] == false && grid[new_x][new_y] != grid[f.curx][f.cury]) // 没有途径过 且 满足可以走的条件
            {
                visit[new_x][new_y] = true;

                from1[new_x][new_y] = dir2[i];
                from2[new_x][new_y][0] = f.curx;
                from2[new_x][new_y][1] = f.cury;

                Q.push(Node(new_x, new_y, f.step + 1));
            }
            else
            {
                continue;
            }
        }
    }
    cout << -1 << endl; // 如果没有在前面 return, 那么输出 -1 说明无解。
}

int main()
{
    cin >> T;
    while (T--)
    {
        init();
        solve();
    }

    return 0;
}