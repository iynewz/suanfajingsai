#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
struct coin
{
    // 金币的结构体
    int nx;
    int ny;
    void down()
    {
        // 金币下落实现,如果y不为0则下落
        if (ny != 0)
            ny -= 1;
    }
    bool havedown()
    {
        // 监测金币是否坐标已经为0
        if (ny == 0)
            return true;
        else
            return false;
    }
};
bool coinscmp(coin a, coin b)
{
    // 金币的y坐标比较,重载排序函数
    return a.ny < b.ny;
}
int main()
{
    int t;
    cin >> t;
    for (int groupn = 0; groupn < t; groupn++)
    {
        int n;
        cin >> n;
        coin coins[n];
        for (int i = 0; i < n; i++)
        {
            // 从0到n-1进行赋值
            cin >> coins[i].nx >> coins[i].ny;
        }
        sort(coins, coins + n, coinscmp);
        // 对金币进行sort排序
        int mx = 0, my = 0, i = 0;
        // i记录当前要接住哪个金币
        bool successful = false;
        // 记录是否成功
        while (1)
        {
            if (i == n)
            {
                // 如果现在要接的金币已经是第n个(不存在的那个)则成功
                successful = true;
                break;
            }
            bool thissuccessful = true;
            // 记录本秒所有要接住的金币是否成功接住
            for (int j = i; j < n; j++)
            {
                // 从i开始到最后一个
                if (coins[j].havedown() == true)
                {
                    // 是不是第j个金币的y已经为0
                    if (mx == coins[j].nx)
                    {
                        i += 1;
                    }
                    else
                    {
                        // 如果接住不
                        thissuccessful = false;
                        break;
                    }
                }
                // 这里可以优化,遇到false跳出
            }
            if (thissuccessful == false)
                break;
            if (mx < coins[i].nx)
                mx += 1;
            if (mx > coins[i].nx)
                mx -= 1;
            for (int j = i; j < n; j++)
                coins[j].down();
            // 自己和金币的移动
        }
        if (successful == true)
            printf("Abletocatch\n");
        else
            printf("Notabletocatch\n");
        // 输出结果
    }
    return 0;
}