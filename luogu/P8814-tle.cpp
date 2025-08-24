// 这个方法好几个数据点 TLE, 只能 60 分

#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

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
        int m = n - e * d + 2; // p + q
        int root = sqrt(n);
        for (int i = 1; i <= root; i++)
        {
            if (p != 0)
            {
                break;
            }
            if (n % i == 0)
            {
                if (m == i + n / i)
                {
                    p = i;
                    q = n / i;
                    break;
                }
            }
            else
            {
                continue;
            }
        }
        if (p != 0)
        {
            cout << p << " " << q << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}