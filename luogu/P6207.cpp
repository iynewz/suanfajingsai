#include <iostream>

using namespace std;
int visit[120][100];
int ans[12000][2]; // 记录走过的点
int cnt = 0;

int r, c;
int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void print_ans()
{
    for (int i = 0; i < cnt; i++)
    {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }
    return;
}

void dfs(int x, int y)
{
    if (x == r && y == c)
    {
        print_ans();
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + direction[i][0];
        int new_y = y + direction[i][1];
        if (!visit[new_x][new_y] && new_x >= 1 && new_x <= r && new_y >= 1 && new_y <= c)
        {
            visit[new_x][new_y] = true; //  第一次做，忘记了
            ans[cnt][0] = new_x;
            ans[cnt][1] = new_y;
            cnt++;
            dfs(new_x, new_y);
            cnt--; // 第一次做，忘记了。递归返回时，撤销这一步（回溯）。
        }
    }
}
int main()
{

    cin >> r >> c;
    char ch;
    for (int i = 1; i <= r; i++) // 存图，从 1 开始
    {
        for (int j = 1; j <= c; j++)
        {
            cin >> ch;
            if (ch == '*')
            {
                visit[i][j] = true; // 障碍，不可访问
            }
            else
            {
                visit[i][j] = false;
            }
        }
    }

    if (!visit[1][1])
    {
        ans[cnt][0] = 1;
        ans[cnt][1] = 1;
        cnt++;
        visit[1][1] = true;
        dfs(1, 1);
    }

    return 0;
}