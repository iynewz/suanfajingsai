#include <iostream>

using namespace std;

int N, M, T;
int SX, SY, FX, FY;
int maze[10][10];
int ans = 0;
int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int visit[10][10] = {0};

void dfs(int x, int y)
{
    if (x == FX && y == FY)
    {

        ans++;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + direction[i][0];
        int new_y = y + direction[i][1];
        if (new_x >= 1 && new_x <= N && new_y >= 1 && new_y <= M && !maze[new_x][new_y] && !visit[new_x][new_y])
        {
            visit[new_x][new_y] = 1;
            dfs(new_x, new_y);
            visit[new_x][new_y] = 0;
        }
    }
}

int main()
{
    cin >> N >> M >> T >> SX >> SY >> FX >> FY;
    int t1, t2;
    for (int i = 0; i < T; i++)
    {
        cin >> t1 >> t2;
        maze[t1][t2] = 1; // 标记障碍
    }
    if (maze[SX][SY] == 1 || maze[FX][FY] == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    visit[SX][SY] = 1;
    dfs(SX, SY);

    cout << ans << endl;
    return 0;
}
