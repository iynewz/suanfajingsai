#include <iostream>
using namespace std;
long long n, L, R;
// int main()
// {
//     cin >> n >> L >> R;
//     if ((R - L) >= n)
//     {
//         cout << n - 1 << endl;
//         return 0;
//     }

//     long long max = 0;
//     for (long long i = L; i <= R; i++)
//     {
//         long long reward = i % n;
//         if (reward > max)
//         {
//             max = reward;
//         }
//     }
//     cout << max << endl;
//     return 0;
// }

int main()
{
    cin >> n >> L >> R;
    if ((R - L) >= n)
    {
        cout << n - 1 << endl;
        return 0;
    }

    cout << R % n << endl;
    return 0;
}