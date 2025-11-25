#include <iostream>
#include <cstring>
using namespace std;
int n;
const int maxn = 16 + 5;
int A[maxn];
int isp[maxn * 2]; // 两数之和是否是 prime, 第一次 TLE 是因为这个数组开小了
bool vis[maxn];

bool is_prime(int x)
{
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}

void dfs(int cur)
{
    if (cur == n && isp[A[0] + A[n - 1]])
    {
        // found solution
        for (int i = 0; i < n; i++)
        {
            if (i != 0)
            {
                printf(" ");
            }
            printf("%d", A[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 2; i <= n; i++)
        {
            if (vis[i] == false && isp[i + A[cur - 1]])
            {
                A[cur] = i;
                vis[i] = true;
                dfs(cur + 1);
                vis[i] = false; // 为什么是在这里清除标志 - 退出分支，撤销刚才的那个选择，让别的分支仍然可以使用数字 i
            }
        }
    }
}
int main()
{
    int kase = 0;
    for (int i = 2; i < 16 * 2; i++)
    {
        isp[i] = is_prime(i);
    }
    while (cin >> n)
    {
        memset(vis, false, sizeof(vis));
        if (kase > 0)
        {
            printf("\n");
        }
        printf("Case %d:\n", ++kase);
        A[0] = 1;
        dfs(1);
    }
    return 0;
}