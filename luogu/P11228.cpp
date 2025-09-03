#include <iostream>

using namespace std;
int T;
int n, m, k, x0, y0, d0;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
char map[1005][1005];

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n >> m >> k;
        cin >> x0 >> y0 >> d0;
        // read map
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> map[i][j];
            }
        }
        map[x0][y0] = 'v'; // visited
        while (k--)
        {
            int new_x = x0 + dir[d0][0];
            int new_y = y0 + dir[d0][1];
            if (1 <= new_x && new_x <= n && 1 <= new_y && new_y <= m && map[new_x][new_y] != 'x')
            {
                x0 = new_x;
                y0 = new_y;
                map[x0][y0] = 'v';
            }
            else
            {
                d0 = (d0 + 1) % 4;
            }
        }
        int count = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (map[i][j] == 'v')
                {
                    count++;
                }
            }
        }
        cout << count << endl;
    }
    return 0;
}