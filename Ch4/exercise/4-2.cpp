// Squares, UVa201
#include <stdio.h>
#include <string.h>
#define maxn 100

int H[maxn][maxn], V[maxn][maxn];        // H[i][j] 表示第 i 行第 j 列是否有右向线段, V[i][j] 表示第 i 行第 j 列是否有下向线段
int right[maxn][maxn], down[maxn][maxn]; // right[i][j]: 从点(i,j)向右的连续水平线段数
                                         // down[j][i]: 从点(i,j)向下的连续垂直线段数
int result[10];                          // result[s] 记录边长为 s 的正方形的数量

int check_make_square(int length, int i, int j)
{ // 以点 (i,j) 为左上角，是否可以构成一个边长 length 的 正方形。已知已经存在 向右、向下 的线段了
    if (down[i][j + length] >= length && right[i + length][j] >= length)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void check(int i, int j) // 对于点(i, j) ，计算它能构成的最大可能边长，并检查每个可能的边长是否满足四个边的条件。
{

    int max_h = right[i][j];
    int max_v = down[i][j];
    int max_s = max_h < max_v ? max_h : max_v;
    // printf("point: (%d, %d), max_h: %d, max_v: %d\n", i, j, max_h, max_v);

    if (max_s == 0)
    {
        return;
    }
    for (int len = 1; len <= max_s; len++)
    {
        if (check_make_square(len, i, j))
        {
            // printf("can make square! len: %d, i:%d, j:%d\n", len, i, j);
            result[len]++;
        }
    }
}

int main()
{
    int n = 0, m;
    int case_count = 1;
    while (scanf("%d", &n) == 1 && n != EOF)
    {
        memset(H, 0, sizeof(H));
        memset(V, 0, sizeof(V));
        memset(right, 0, sizeof(H));
        memset(down, 0, sizeof(V));
        memset(result, 0, sizeof(result));
        scanf("%d", &m);
        while (m--) // 存储水平和垂直线段的存在情况
        {
            char dir[2];
            int a, b;
            scanf("%s%d%d", dir, &a, &b);
            if (strcmp(dir, "V") == 0)
            {
                V[b][a] = 1; // 注意这里顺序是 b a
            }
            else
            {
                H[a][b] = 1;
            }
        }

        // 预处理 right 和 down 数组
        for (int i = 1; i <= n; i++)
        {
            for (int j = n - 1; j >= 1; j--)
            {
                if (H[i][j])
                {
                    right[i][j] = right[i][j + 1] + 1;
                }
                else
                {
                    right[i][j] = 0;
                }
            }
        }

        for (int j = 1; j <= n; j++) // j 是列
        {
            for (int i = n - 1; i >= 1; i--) // i 是行
            {
                if (V[i][j])
                {
                    down[i][j] = down[i + 1][j] + 1;
                }
                else
                {
                    down[i][j] = 0;
                }
            }
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                check(i, j);
            }
        }

        int has_output = 0;
        if (case_count > 1)
        {
            printf("\n**********************************\n\n");
        }
        printf("Problem #%d\n\n", case_count);

        for (int i = 1; i < 10; i++)
        {
            if (result[i] > 0)
            {
                printf("%d square (s) of size %d\n", result[i], i);
                has_output = 1;
            }
        }
        if (has_output == 0)
        {
            printf("No completed squares can be found.\n");
        }

        case_count++;
    }
    return 0;
}