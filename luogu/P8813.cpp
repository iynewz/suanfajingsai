// 输出共一行，如果 a^b 的值不超过 10^9，则输出 a^b，否则输出 -1
#include <iostream>
using namespace std;

int main()
{
    long long a, b;
    cin >> a >> b;
    long long max = 1000000000;
    long long ans = 1;
    for (int i = 0; i < b; i++)
    {
        if (a == 1)
        {
            cout << a << endl;
            return 0;
        }
        ans *= a;
        if (ans > max)
        {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << ans << endl;
    return 0;
}