#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 500 + 5;
int N;
int m, k;
long long a[maxn];

// 能否把输入序列划分成 k 个连续的子序列，使得所有 S(i) 均不超过 x
bool P(long long x) {
  long long sum = 0;
  int group = 1;
  for (int i = 0; i < m; i++) {
    if (a[i] > x) {
      return false; // 重要，‼️ 第一次写死循环错在这里
    }
    if (sum + a[i] <= x) {
      sum += a[i];
    } else {
      group++;
      sum = a[i]; // 当前元素放入新段
    }
  }
  return group <= k;
}
// 从后往前，让后面的段尽量大，因为题目要求字典序最小
void print_ans(int limit) {
  bool cut[maxn] = {false};
  long sum = 0;
  int interval = k - 1; // 还需要切多少刀
  for (int i = m - 1; i >= 0; i--) {
    if (sum + a[i] > limit || i < interval) {
      cut[i] = true; // i 后面切一刀
      sum = a[i];
      interval--;
    } else {
      sum += a[i];
    }
  }

  for (int i = 0; i < m; i++) {
    cout << a[i];
    if (i != m - 1) {
      cout << " ";
    }
    if (cut[i]) {
      cout << "/ ";
    }
  }
  cout << endl;
}

int main() {
  cin >> N;
  while (N--) {

    cin >> m >> k;
    long long l = 0, r = 0;
    for (int i = 0; i < m; i++) {
      cin >> a[i];
      r += a[i];
      l = max(l, a[i]); // 下界：最大元素‼️
    }
    // 二分最小值 x, 找最小的满足 P(x) 的值
    while (l < r) {
      long long mid = l + (r - l) / 2;
      if (!P(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    // 找到了 每段的和 ≤ l
    // cout << l << endl;
    print_ans(l);
  }
  return 0;
}