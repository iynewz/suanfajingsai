#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;
// 1827 51425
int main()
{
    int k;
    cin >> k;
    while (k--)
    {
        long long n, d, e;
        long long p = 0, q = 0;
        cin >> n >> d >> e;
        // n = p * q;
        // e * d - 1 = (p - 1)(q - 1) ;
        long long m = n - e * d + 2; // p + q
        // p, q 是 x^2 - m * x + n = 0 的 2 个 解
        long long delta = m * m - 4 * n;
        if (delta < 0)
        {
            cout << "NO" << endl;
            continue;
        }
        long long delta_root = sqrt(delta); // long long! 第一次忘记了，有好几个测试点 WA

        if (delta_root * delta_root != delta) // 根号 delta 是无理数
        {
            cout << "NO" << endl;
            continue;
        }
        p = (m - delta_root) / 2; // 直接算出，但可以 int 取整了
        q = (m + delta_root) / 2;
        if (p > 0 && q > 0 && p * q == n && p + q == m)
        { // 所以还要再判断一下
            cout << p << " " << q << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}