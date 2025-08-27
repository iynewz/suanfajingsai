#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n, 1);
        dp[0] = 1;
        int max_len = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_len = max(max_len, dp[i]);
        }
        return max_len;
    }
};

// 你自己需要写的 main 函数
int main()
{
    Solution solution;

    vector<int> nums = {0};
    int result = solution.lengthOfLIS(nums);

    cout << "最长递增子序列长度: " << result << endl; // 输出 4
    return 0;
}