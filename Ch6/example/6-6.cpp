#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define maxn 21

bool flag[1 << maxn]; // 2^20

int main()
{

    int case_number;
    int D, I;
    cin >> case_number;
    while (case_number--)
    {
        memset(flag, false, sizeof(flag));
        cin >> D >> I;
        int k;
        int k_max = (1 << D) - 1; // 2^D - 1
        for (int i = 0; i < I; i++)
        {
            k = 1;
            while (k <= k_max)
            {
                int temp = flag[k];
                flag[k] = !flag[k];
                k = temp == 0 ? 2 * k : 2 * k + 1;
            }
        }
        cout << (k / 2) << endl;
    }
    return 0;
}