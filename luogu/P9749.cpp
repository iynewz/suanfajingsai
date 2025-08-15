#include <iostream>
using namespace std;

long long n, d;
long long a[100000 + 5]; // a[i] 表示离上一个节点的距离
long long b[100000 + 5]; // /b[i]  表示当前节点油价
long long r;             // 现有汽油
long long p;             // 最低价
long long s;             // 行驶距离
long long ans;

int main()
{
    cin >> n >> d;

    for (int i = 2; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    r = 0;
    p = b[1];
    s = 0;
    for (int i = 2; i <= n; i++)
    {
        s += a[i];
        if (s > r * d) // 需要额外加油
        {
            long long need = (s - r * d + d - 1) / d; // 额外加油的数量
            r += need;
            ans += p * need;
        }

        p = min(b[i], p);
    }
    cout << ans << endl;

    return 0;
}
