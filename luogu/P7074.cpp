#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
const int N = 1005;
const int inf = 1e9;
long long grid[N][N];
long long f[N][N][3]; // f[i][j] 表示取数到 (i,j) 时的最大值，k=0 表示从左来的，k=1 表示从上来的，k=2 表示从下来的

void init()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            f[i][j][0] = f[i][j][1] = f[i][j][2] = -inf;
        }
    }
}

void solve()
{
    f[1][0][0] = 0;
    for (int j = 1; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            // 从左来
            long long mx = -inf;
            mx = max(f[i][j - 1][0], mx);
            mx = max(f[i][j - 1][1], mx);
            mx = max(f[i][j - 1][2], mx);
            if (mx != -inf)
            {
                f[i][j][0] = mx + grid[i][j];
            }
            // 从上来
            mx = -inf;
            mx = max(f[i - 1][j][0], mx);
            mx = max(f[i - 1][j][1], mx);
            if (mx != -inf)
            {
                f[i][j][1] = mx + grid[i][j];
            }
        }
        // 从下来
        for (int i = n - 1; i >= 1; i--)
        {
            long long mx = -inf;
            mx = max(f[i + 1][j][0], mx);
            mx = max(f[i + 1][j][2], mx);
            if (mx != -inf)
            {
                f[i][j][2] = mx + grid[i][j];
            }
        }
    }
    cout << max(f[n][m][0], f[n][m][1]) << endl;
}

int main()
{
    init();
    solve();
    return 0;
}