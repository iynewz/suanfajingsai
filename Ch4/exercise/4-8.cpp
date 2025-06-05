// Extraordinarily Tired Students, UVa 12108
#include <stdio.h>
#include <string.h>
#define max_student 10
#define max_time 2000

int a[max_student];                   // 清醒
int b[max_student];                   // 睡
int c[max_student];                   // offset
int state_log[max_time][max_student]; // 记录每个学生在每个时间点的状态
int n;

int main()
{
    int case_num = 1;
    while (scanf("%d", &n) == 1 && n != 0)
    {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        memset(state_log, 0, state_log[0][0] * sizeof(int));

        for (int i = 0; i < n; i++)
        {
            scanf("%d %d %d", &a[i], &b[i], &c[i]);
        }
        int time = 1;
        while (1)
        {
            int all_awake = 1;
            int no_result = 0;
            for (int i = 0; i < n; i++)
            {
                if (c[i] > a[i])
                {
                    all_awake = 0;
                    break;
                }
            }
            if (all_awake)
            {
                printf("Case %d: %d\n", case_num++, time);
                break;
            }

            // 检查是否会无限循环，也就是这个 state log 之前出现过吗？
            for (int t = 1; t < time; t++)
            {
                int same = 1;
                for (int i = 0; i < n; i++)
                {
                    if (state_log[t][i] != state_log[time][i])
                    {
                        same = 0;
                        break;
                    }
                }
                if (same == 1)
                {
                    // 这个时刻之前出现过!
                    no_result = 1;
                    break;
                }
            }

            if (no_result)
            {
                printf("Case %d: %d\n", case_num++, -1);
                break;
            }

            // 记录当前状态
            for (int i = 0; i < n; i++)
            {
                state_log[time][i] = c[i];
            }

            // calculate_awake
            int awake = 0;
            for (int i = 0; i < n; i++)
            {
                if (c[i] >= 1 && c[i] <= a[i])
                {
                    awake++;
                }
            }

            // 更新所有学生的状态
            for (int i = 0; i < n; i++)
            {
                if (c[i] == a[i])
                {
                    if ((n - awake) > awake) // asleep > awake
                    {
                        c[i]++;
                    }
                    else
                    {
                        c[i] = 1; // 再醒一轮
                    }
                }
                else if (c[i] == a[i] + b[i])
                {
                    c[i] = 1;
                }
                else
                {
                    c[i]++;
                }
            }

            time++;
        }
    }

    return 0;
}