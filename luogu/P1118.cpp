// P1118
#include <stdio.h>

int main()
{
    int n, sum;
    scanf("%d %d", &n, &sum);
    if (n == 1)
    {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int sum_others = (1 + n) * n / 2 - i - j;
            int current_sum = i + j + (n - 1) * sum_others;
            if (current_sum == sum)
            {
                printf("%d ", i);
                for (int k = 1; k <= n; k++)
                {
                    if (k != i && k != j)
                    {
                        printf("%d ", k);
                    }
                }
                printf("%d\n", j);
                return 0;
            }
        }
    }
    return 0;
}