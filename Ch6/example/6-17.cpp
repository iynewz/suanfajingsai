#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

const int maxn = 200 + 5;
int T, n;
char buf[maxn][maxn];

void dfs(int r, int c)
{
    printf("%c(", buf[r][c]);
    if (r + 1 < n && buf[r + 1][c] == '|')
    {
        int i = c;
        while (i - 1 >= 0 && buf[r + 2][i - 1] == '-')
        {
            i--; // 找 ---- 的左边界
        }
        while (buf[r + 2][i] == '-' && buf[r + 3][i] != '\0')
        { // 沿着 '----' 向右扫描
            if (!isspace(buf[r + 3][i]))
            {
                dfs(r + 3, i); // fgets读入的'\n'也满足isspace()
            }
            i++;
        }
    }
    printf(")");
}

void solve()
{
    n = 0;
    for (;;)
    {
        fgets(buf[n], maxn, stdin);
        if (buf[n][0] == '#')
        {
            break;
        }
        else
        {
            n++;
        }
    }
    printf("(");
    if (n)
    {
        for (int i = 0; i < strlen(buf[0]); i++)
        {
            if (buf[0][i] != ' ')
            {
                dfs(0, i); // 从根节点开始 dfs
                break;
            }
        }
    }
    printf(")\n");
}

int main()
{
    fgets(buf[0], maxn, stdin);
    sscanf(buf[0], "%d", &T);
    while (T--)
    {
        solve();
    }
    return 0;
}