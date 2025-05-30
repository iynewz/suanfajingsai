// P2694 接金币
#include <stdio.h>
#include <string.h>
#include <cmath>

#define maxn 55

int main()
{
    int g;
    scanf("%d", &g);
    int coin[maxn][2];
    while (g--)
    {
        int n;
        scanf("%d", &n);
        memset(coin, 0, sizeof(coin));
        int all_catch = 1;
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &coin[i][0], &coin[i][1]);
        }
        // 对于 coin[i], 按照 coin[i][1] 的值从小到大排序
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (coin[j][1] > coin[j + 1][1])
                {
                    // swap coin[j] and coin [j + 1]
                    int temp[2] = {coin[j][0], coin[j][1]};
                    coin[j][0] = coin[j + 1][0];
                    coin[j][1] = coin[j + 1][1];
                    coin[j + 1][0] = temp[0];
                    coin[j + 1][1] = temp[1];
                }
            }
        }

        // 检查是否可接住所有金币
        int curr_x = 0;
        int time_used = 0;
        for (int i = 0; i < n; i++)
        {
            int coin_time = coin[i][1] - time_used;   // 当前金币还有多久落地
            int time_need = abs(coin[i][0] - curr_x); // 移动到金币位置所需时间
            if (time_need > coin_time)
            {
                all_catch = 0; // 这个金币接不住
                break;
            }
            else
            {
                curr_x = coin[i][0];    // 更新当前位置
                                        // time_used += time_need; // 不对
                time_used += coin_time; // 更新已用时间
            }
        }

        printf(all_catch ? "Abletocatch\n" : "Notabletocatch\n");
    }
    return 0;
}