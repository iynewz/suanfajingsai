#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    if ((n & 1) == 1)
    {
        cout << -1 << endl;
        return 0;
    }
    int first_flag = 0;
    for (int k = 25; k >= 1; --k) // 从 2^25 检查到 2^1
    {
        int mask = 1 << k;
        // cout << k << " " << mask << endl;
        if ((n & mask) == mask)
        {
            if (first_flag)
            {
                cout << " ";
            }

            cout << mask;
            first_flag = 1;
        }
    }
    cout << endl;

    return 0;
}
