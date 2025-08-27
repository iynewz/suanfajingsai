#include <iostream>
#include <algorithm>
using namespace std;
int n, k;
const int maxn = 500 + 5;
pair<int, int> points[maxn];
int dp[maxn][maxn]; // dp[i][p] - 以 i 结尾，且已经插入了最多 p 个额外点的最长上升点序列最大长度

int main()
{
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> points[i].first >> points[i].second;
    }
    sort(points + 1, points + n + 1);
    // initialize
    for (int i = 1; i <= n; i++)
    {
        for (int p = 0; p <= k; p++) // 第一次写错了，p <= k
        {
            dp[i][p] = 1 + p; // 直接在 i 点前插入 p 个点
        }
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (points[i].second < points[j].second)
            {
                continue;
            }
            int d = points[i].first - points[j].first - 1 + points[i].second - points[j].second; // 至少得插入 d 个点才可以步长为 1 连起来

            for (int p = d; p <= k; p++) // p 的起点是 d, 不是 0
            {
                dp[i][p] = max(dp[j][p - d] + d + 1, dp[i][p]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dp[i][k]); // k
    }
    cout << ans << endl;
    return 0;
}