#include <iostream>

using namespace std;
int n, m;
char grid[100 + 5][100 + 5];

int calculate(const int &x, const int &y)
{
    int ans = 0;
    int direction[8][2] = {
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, 1},
        {0, -1},
        {1, 1},
        {1, 0},
        {1, -1},
    };
    for (int i = 0; i < 8; i++)
    {
        int new_x = x + direction[i][0];
        int new_y = y + direction[i][1];
        if (new_x <= -1 || new_y <= -1 || new_y >= m || new_x >= n)
        {
            continue;
        }
        else
        {
            if (grid[new_x][new_y] == '*')
            {
                ans++;
            }
        }
    }
    return ans;
}
int main()
{

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '*')
            {
                cout << '*';
            }
            else
            {
                int ans = calculate(i, j);
                cout << ans;
            }
        }
        if (i != (n - 1))
        {
            cout << endl;
        }
    }

    return 0;
}