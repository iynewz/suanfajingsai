#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int T;
int n;
int a[100000 + 5];

int avg;

int main()
{
    cin >> T;
    while (T--)
    {
        long long total = 0;
        long long ans = 0;

        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            total += a[i];
        }
        sort(a + 1, a + n + 1);
        if (a[1] == a[n])
        {
            cout << 0 << endl;
        }
        else
        {
            long long avg = total / n;
            // cout << "avg " << avg << endl;
            for (int i = 1; i <= n; i++)
            {
                if (a[i] > avg)
                {
                    ans += (a[i] - avg);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}