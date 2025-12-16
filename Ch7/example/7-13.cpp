#include <cstdio>
#include <algorithm>
int maxd;
int n;
int a[20]; // 长度为 d 的加减链 a[0..d]
const int maxans = 13;
bool dfs(int d, int maxd)
{
    if (a[d] == n)
    {
        return true;
    }
    if (d == maxd)
    {
        return false;
    }
    int maxv = a[0];
    for (int i = 1; i <= d; i++)
    {
        maxv = std::max(a[i], maxv);
    }
    if ((maxv << (maxd - d)) < n)
    {
        return false;
    }
    for (int i = d; i >= 0; i--)
    {
        a[d + 1] = a[d] + a[i]; // 尝试加法
        if (dfs(d + 1, maxd))
        {
            return true;
        }
        a[d + 1] = a[d] - a[i];
        if (dfs(d + 1, maxd))
        {
            return true;
        }
    }
    return false;
}
int solve(int n)
{
    if (n == 1)
    {
        return 0;
    }

    a[0] = 1;
    for (maxd = 1; maxd < maxans; maxd++)
    {
        if (dfs(0, maxd))
        {
            return maxd;
        }
    }
    return maxans;
}

int main()
{
    while (scanf("%d", &n) == 1 && n)
    {
        int ans = solve(n);
        printf("%d\n", ans);
    }

    return 0;
}