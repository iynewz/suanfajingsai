// 最长递增子序列（LIS） 的 O(n²) 版本
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> nums;
  vector<int> memo; // 用于记忆化

  // dfs(i) 表示以 nums[i] 结尾的 LIS 长度
  int dfs(int i) {
    if (memo[i] != -1)
      return memo[i];

    int res = 1; // 至少 nums[i] 自身长度为 1
    for (int j = 0; j < i; j++) {
      if (nums[j] < nums[i]) {
        res = max(res, dfs(j) + 1);
      }
    }
    memo[i] = res;
    return res;
  }

  int lengthOfLIS(vector<int> &input) {
    nums = input;
    int n = nums.size();
    memo.assign(n, -1); // 初始化记忆化数组

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans = max(ans, dfs(i));
    }
    return ans;
  }
};

int main() {
  vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

  Solution sol;
  cout << sol.lengthOfLIS(nums);

  return 0;
}