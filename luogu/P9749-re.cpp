
#include <iostream>
using namespace std;
int main()
{
    // v数组就到下一站点的总路程, a记录每一站的油价
    int n, d, v[10001], a[10001], ans = 0;
    cin >> n >> d;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> v[i];
        if (i != 0)
            v[i] += v[i - 1]; // 路程和
    }
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int mina = a[0], nu = 0; // mina用于记录当前最低油价 nu 记录已购买油的体积
    for (int i = 0; i < n - 1; i++)
    {
        int zu = (v[i] + d - 1) / d; // 计算当前需要多少升油

        mina = min(mina, a[i]);  // 当前最低油价
        ans += (zu - nu) * mina; // 最少价钱为(需要的油-已购的油)*当前最低油价
        nu = zu;                 // 花钱了更新已购油的体积
    }
    cout << ans << endl;
    return 0;
}
