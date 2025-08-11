#include <iostream>
using namespace std;

int T, N;
int dp[1001];
int main()
{
    int temph, tempm, t1, t2, T, N;
    char ch;
    cin >> temph >> ch >> tempm;
    t1 = temph * 60 + tempm;
    cin >> temph >> ch >> tempm;
    t2 = temph * 60 + tempm;
    T = t2 - t1;
    cin >> N;
    int t, c, p;

    for (int i = 0; i < N; i++)
    {
        cin >> t >> c >> p; // 读取每棵樱花树的时间、美学值和次数
        if (p == 0)
        {
            // 完全背包
            for (int j = t; j <= T; ++j)
            {
                dp[j] = max(dp[j], dp[j - t] + c);
            }
        }
        else if (p == 1)
        {
            // 01背包
            for (int j = T; j >= t; --j)
            {
                dp[j] = max(dp[j], dp[j - t] + c);
            }
        }
        else
        {
            // 多重背包
            int k = 1;
            while (k <= p)
            {
                int new_t = t * k;
                int new_c = c * k;
                for (int j = T; j >= new_t; --j)
                {
                    dp[j] = max(dp[j], dp[j - new_t] + new_c);
                }
                p -= k;
                k *= 2;
            }
            if (p > 0)
            {
                int new_t = t * p;
                int new_c = c * p;
                for (int j = T; j >= new_t; --j)
                {
                    dp[j] = max(dp[j], dp[j - new_t] + new_c);
                }
            }
        }
    }
    cout << dp[T] << endl; // 输出最大美学值
    return 0;
}