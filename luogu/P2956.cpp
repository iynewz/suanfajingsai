// P2956[USACO09OCT] The Robot Plow G
#include <cstdio>
#define maxn 250
int main()
{
    int grid[maxn][maxn] = {0};
    int x, y, count;
    scanf("%d %d %d", &x, &y, &count);

    int l_a, l_b;
    int r_a, r_b;
    for (int i = 0; i < count; i++)
    {
        scanf("%d %d %d %d", &l_a, &l_b, &r_a, &r_b);
        for (int j = l_a; j <= r_a; j++)
        {
            for (int k = l_b; k <= r_b; k++)
            {
                grid[j][k] = 1;
            }
        }
    }
    int total = 0;
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            if (grid[i][j] == 1)
            {
                total++;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}