// WA

#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
    {
        int n, s1, v1, s2, v2;
        scanf("%d%d%d%d%d", &n, &s1, &v1, &s2, &v2);
        // 问题：乘法在 int 范围内先计算，若结果超过 INT_MAX 就溢出，之后再赋给 ll 也救不回来了
        ll unit = s1 * s2;
        ll unit_v = max(s2 * v1, s1 * v2);
        ll ans1 = n / unit * unit_v;
        n = n % unit; // remain space
        if (s2 > s1)
        {
            swap(s1, s2);
            swap(v1, v2);
        }
        // s1 >= s2
        ll ans2 = 0;
        for (ll j = 0; j * s1 <= n; j++) // take i 个宝物 1
        {
            int cnt2 = (n - j * s1) / s2;
            ll cur = j * v1 + cnt2 * v2;
            ans2 = max(ans2, cur);
        }
        printf("Case #%d: %lld\n", i, ans1 + ans2);
    }
    return 0;
}