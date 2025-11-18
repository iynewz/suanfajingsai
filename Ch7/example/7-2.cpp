#include <iostream>
using namespace std;
int a[20];

int main()
{
    int N;
    int caseNum = 0;
    while (cin >> N)
    {
        for (int i = 1; i <= N; i++)
        {
            cin >> a[i];
        }
        long long ans = 0; // you should consider 0 as the value of the maximum product.
        for (int l = 1; l <= N; l++)
        {
            for (int r = l; r <= N; r++)
            {
                long long tmp = 1;
                for (int i = l; i <= r; i++)
                {
                    tmp *= a[i];
                }
                ans = max(ans, tmp);
            }
        }
        cout << "Case #" << ++caseNum << ": The maximum product is " << ans << "." << endl
             << endl;
    }
    return 0;
}