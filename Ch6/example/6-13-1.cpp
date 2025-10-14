#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int maxh = 200 + 5;
const int maxw = 50 * 4 + 5;

int H, W;
char c;
int idx[maxh][maxw];
int bit[maxh][maxw];
int visited[maxh][maxw];
int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void hexCharToBinary(char hexChar, int i, int j)
{
    int value; // decimal value
    if (hexChar >= '0' && hexChar <= '9')
    {
        value = hexChar - '0';
    }
    else if (hexChar >= 'a' && hexChar <= 'f')
    {
        value = hexChar - 'a' + 10;
    }
    // 转换为 4 位二进制字符串
    for (int k = 3; k >= 0; k--)
    {
        bit[i][j * 4 + k] = value % 2;
        value /= 2;
    }
    return;
}

void test_print()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W * 4; j++)
        {
            cout << bit[i][j];
        }
        cout << endl;
    }
    return;
}

void dfs_black(int r, int c, int id)
{
    if (r < 0 || r >= H || c < 0 || c >= W * 4)
    {
        return;
    }
    if (bit[r][c] == 0 || idx[r][c] > 0)
    {
        return;
    }
    idx[r][c] = id;
    for (int i = 0; i < 4; i++)
    {
        int dx = direction[i][0];
        int dy = direction[i][1];
        dfs_black(r + dx, c + dy, id);
    }
}

void dfs_white(int r, int c, int &surrounding_label, bool &touch_boundary)
{
    if (r < 0 || r >= H || c < 0 || c >= W * 4)
    {
        touch_boundary = true;
        return;
    }
    if (visited[r][c])
    {
        return;
    }

    if (bit[r][c] == 1)
    {
        int cur_label = idx[r][c];
        if (surrounding_label == -1)
        {
            surrounding_label = cur_label;
        }
        else if (surrounding_label != cur_label)
        { // 不是有效空洞
            surrounding_label = -2;
        }
        return;
    }
    visited[r][c] = 1;
    for (int i = 0; i < 4; i++)
    {
        int dx = direction[i][0];
        int dy = direction[i][1];
        dfs_white(r + dx, c + dy, surrounding_label, touch_boundary);
    }
}

int main()
{
    int T = 0;
    while (scanf("%d%d", &H, &W) == 2 && H && W)
    {
        getchar(); // get rid of the ending \n
        memset(bit, 0, sizeof(bit));
        memset(idx, 0, sizeof(idx));
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                scanf("%c", &c);
                // hex to binary, save to bit[][]
                hexCharToBinary(c, i, j);
            }
            getchar(); // get rid of the ending \n
        }

        // test_print();

        // flood fill 统计图形总数
        int black_cnt = 0;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W * 4; j++)
            {
                if (idx[i][j] == 0 && bit[i][j] == 1)
                {
                    dfs_black(i, j, ++black_cnt);
                }
            }
        }

        // cout << "black_cnt: " << black_cnt << endl;

        // 统计每个图形的空洞数
        vector<int> holes_count(black_cnt + 1, 0); // 容易错！索引从 1 到 black_cnt
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W * 4; j++)
            {
                if (bit[i][j] == 0 && !visited[i][j])
                {
                    int surrounding_label = -1;
                    bool touch_boundary = false;

                    dfs_white(i, j, surrounding_label, touch_boundary);

                    if (touch_boundary == 0 && surrounding_label > 0)
                    {
                        holes_count[surrounding_label]++;
                    }
                }
            }
        }

        string ans = "";
        for (int i = 1; i <= black_cnt; i++)
        {
            int holes = holes_count[i];

            // cout << holes << endl;
            char ch;
            switch (holes)
            {
            case 1:
                ch = 'A';
                break;
            case 3:
                ch = 'J';
                break;
            case 5:
                ch = 'D';
                break;
            case 4:
                ch = 'S';
                break;
            case 0:
                ch = 'W';
                break;
            case 2:
                ch = 'K';
                break;
            }
            ans += ch;
        }
        sort(ans.begin(), ans.end());
        cout << "Case " << ++T << ": " << ans << endl;
    }
    return 0;
}