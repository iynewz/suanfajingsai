// -7/2+3*sqrt(5)/2
//
// k1 / k2 + k3 * sqrt(k4) / k5

#include <iostream>
using namespace std;
#include <math.h>

int T, M, a, b, c;
int k1, k2, k3, k4, k5;

int get_gcd(int x, int y)
{
    if (x % y == 0)
    {
        return y;
    }
    return get_gcd(y, x % y);
}

void calc_1(int x, int y)
{ // 约分，输出 k1 / k2
    if (x == 0)
    {
        cout << 0;
        return;
    }
    if (x * y < 0) // 有一个负数
    {
        cout << '-';
    }
    k1 = abs(x);
    k2 = abs(y);
    int gcd = get_gcd(k1 >= k2 ? k1 : k2, k1 <= k2 ? k1 : k2);
    k1 = k1 / gcd; // 除以最大公约数
    k2 = k2 / gcd;
    cout << k1;
    if (k2 != 1)
    {
        cout << "/" << k2;
    }
}

// void calc_2(int x)
// { // 根号化简，把 sqrt(200) 化简为 10*sqrt(2) 的格式
//     int root = sqrt(x);
//     int found = 0;
//     for (int i = root; i >= 0; i--)
//     {
//         if (found == 1)
//         {
//             break;
//         }
//         for (int j = 1; j <= x; j++)
//         {
//             if (i * i * j == x)
//             {
//                 k3 = i;
//                 k4 = j;
//                 found = 1;
//                 break;
//             }
//         }
//     }
//     // 不能直接输出 k3， 因为可能可以继续约分。
//     return;
// }

void calc_2(int x)
{
    k3 = 1;
    k4 = 1;
    for (int i = 2; i * i <= x; i++)
    {
        while (x % i == 0)
        {
            if (x % (i * i) == 0)
            {
                k3 = k3 * i;
                x /= (i * i);
            }
            else
            {
                k4 = k4 * i;
                x /= i;
            }
        }
    }
    k4 *= x;
    return;
}

int main()
{
    cin >> T >> M;
    while (T--)
    {
        cin >> a >> b >> c;
        int delta = b * b - 4 * a * c;
        if (delta < 0)
        {
            cout << "NO" << endl;
            continue;
        }
        if (delta == 0) // 一定无根号
        {
            calc_1(-b, 2 * a);
            cout << endl;
            continue;
        }
        else
        {
            double tmp_root = sqrt(delta);
            // 1. delta 为完全平方
            if (int(tmp_root) * int(tmp_root) == delta)
            {
                if (a > 0)
                {
                    calc_1(-b + int(tmp_root), 2 * a);
                }
                else
                {
                    calc_1(-b - int(tmp_root), 2 * a);
                }
                cout << endl;
            }
            else // 2. delta 不为完全平方
            {
                if (b != 0)
                {
                    calc_1(-b, 2 * a);
                    cout << '+';
                }
                calc_2(delta); // k3, k4 赋值。k3 和 k5 可能可以继续约分。

                a = abs(a); // 漏了 abs
                int gcd = get_gcd(k3, 2 * a);
                k3 = k3 / gcd;
                k5 = 2 * a / gcd; // 这样保证 是 正数
                if (k3 != 1)
                {
                    cout << k3 << "*";
                }
                cout << "sqrt(" << k4 << ")";
                if (k5 != 1)
                {
                    cout << "/" << k5;
                }
                cout << endl;
            }
        }
    }

    return 0;
}