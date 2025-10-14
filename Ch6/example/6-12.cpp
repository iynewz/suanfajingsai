#include <iostream>
#include <cstring>

const int maxn = 100 + 5;
int m, n;
int idx[maxn][maxn];
char pic[maxn][maxn];

void dfs(int r, int c, int id)
{
    if (r < 0 || r >= m || c < 0 || c >= n)
    {
        return;
    }
    if (pic[r][c] == '*' || idx[r][c] > 0)
    {
        return;
    }
    idx[r][c] = id;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0)
            {
                dfs(r + dx, c + dy, id);
            }
        }
    }
}
int main()
{
    while (scanf("%d%d", &m, &n) == 2 && m != 0 && n != 0)
    {
        for (int i = 0; i < m; i++)
        {
            scanf("%s", pic[i]);
        }
        memset(idx, 0, sizeof(idx));

        int cnt = 0;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (idx[i][j] == 0 && pic[i][j] == '@')
                {
                    dfs(i, j, ++cnt);
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}