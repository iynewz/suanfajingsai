// 答案对的，缺剪枝
#include <algorithm>
#include <cstdio>
#include <functional> // Required for std::greater
#include <iostream>
#include <vector>

using namespace std;
vector<int> parts;
// used[i] 表示 parts[i] 是否被使用
vector<bool> used;
int maxd;

/**
是否能把所有小段拼成若干根长度为 maxd 的木棍
cur_len：当前这根木棍已经拼了多长，<= maxd
start_pos：在“当前这根木棍”中，下一个小段只能从 start_pos 往后选
*/

bool dfs(int cur_len, int start_pos) {
  int parts_len = parts.size();

  if (cur_len == 0) {
    bool hasResult = true;
    for (int k = 0; k < parts_len; k++) {
      if (used[k] == false) {
        hasResult = false;
      }
    }
    if (hasResult) {
      return true;
    }
  }

  int prev = -1;

  for (int i = start_pos; i < parts_len; i++) {
    if (used[i] == true) {
      continue;
    }
    if (parts[i] == prev) {
      continue;
    }
    if (parts[i] + cur_len > maxd) {
      continue;
    }
    if (parts[i] + cur_len == maxd) {
      used[i] = true;
      if (dfs(0, 0)) {
        return true;
      }
      used[i] = false;
    }

    if (parts[i] + cur_len < maxd) {
      used[i] = true;
      if (dfs(parts[i] + cur_len, i + 1)) {
        return true;
      } else {
        used[i] = false;
      }
    }
    prev = parts[i];
    if (cur_len == 0) {
      return false;
    }
  }
  return false;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1 && n != 0) {
    parts.clear();
    for (int i = 0; i < n; i++) {
      int a;
      scanf("%d", &a);
      parts.push_back(a);
    }
    // sort(parts.begin(), parts.end(), greater<int>());
    // for (auto i : parts) {
    //   cout << i << " ";
    // }
    sort(parts.begin(), parts.end(), greater<int>());
    used.assign(parts.size(), false);
    int max_value = parts[0];

    for (maxd = max_value;; maxd++) {
      if (dfs(0, 0)) {
        printf("%d\n", maxd);
        break; // 漏了
      }
    }
  }
  return 0;
}