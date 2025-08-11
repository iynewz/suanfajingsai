#include <iostream>
using namespace std;

int a, b, p;

long long qpow(long long a, long long b)
{ // a 是底， b 是幂
    long long ans = 1;
    while (b > 0)
    {
        if (b & 1)
        { // 得到 b 二进制的最后一位
            ans = a * ans;
            ans = ans % p;
        }
        a = a * a; // 获取下一个
        a = a % p; // 过程中取余防止溢出
        b = b >> 1;
    }
    return ans;
}

//(a^b)mod p
int main()
{

    cin >> a >> b >> p;
    long long ans = qpow(a, b);
    cout << a << "^" << b << " mod " << p << "=" << ans << endl;
    return 0;
}
