// n = 10^9 会超时, 只能拿 50 分

#include <iostream>
#include <cmath>
using namespace std;

// int main()
// {
//     int n;
//     cin >> n;
//     int a[10000];
//     int counter;
//     int taken = 0;
//     int day = 0;
//     int day_n;
//     while (taken < n)
//     {
//         day++;
//         counter = 0;
//         // 1 2 3 4 5 6 7 8
//         for (int i = 1; i <= n; i++)
//         {
//             if (a[i] == 1)
//             {
//                 continue;
//             }
//             if (a[i] == 0)
//             {
//                 counter++;
//             }
//             if (counter % 3 == 1)
//             {
//                 a[i] = 1; // 标记为取走
//                 taken++;
//                 if (i == n)
//                 {
//                     day_n = day;
//                 }
//             }
//         }
//     }
//     cout << day << " " << day_n << endl;

//     return 0;
// }

int main()
{
    int n;
    int day = 0, day_n = 0;
    cin >> n;

    while (n)
    {
        day++;
        if (day_n == 0 && n % 3 == 1) // 只有在第一次 n % 3 == 1 时记录答案
            day_n = day;
        n -= ceil(n / 3.0);
    }

    cout << day << ' ' << day_n << '\n';

    return 0;
}