#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 20 + 5;
int n;
int a[5];        // a[0] = 10000
int delay[maxn]; // 合法启动间隔(从最小到最大)
int ans;         // final ans
int cnt;         // 可行的延迟

bool ok(int *p, int k) //判断延迟 k 时间片后放程序是否冲突
{
  for (int i = 0; i < 5; i++) {
    if ((a[i] & (p[i] >> k))) {
      return false;
    }
  }
  return true;
};
/*
d - 已经安排好的程序数量
*/

void dfs(int *p, int d, int sum) {
  if (d == 10) {
    ans = min(ans, sum);
    return;
  }
  if (sum + delay[0] * (10 - d) >= ans) {
    return;
  }
  for (int i = 0; i < cnt; i++) {
    if (ok(p, delay[i])) {
      int p2[5];
      for (int j = 0; j < 5; j++) {
        p2[j] = (p[j] >> delay[i]) | a[j];
      }
      dfs(p2, d + 1, sum + delay[i]);
    }
  }
  return;
}

void init() {
  memset(a, 0, sizeof(a));
  memset(delay, 0, sizeof(delay));
  ans = maxn * 10; // 设为一个比较大的值
  return;
}

int main() {
  while (scanf("%d", &n) == 1 && n) {
    init();
    for (int i = 0; i < 5; i++) {
      char line[maxn];
      scanf("%s", line);

      for (int j = 0; j < n; j++) {
        if (line[j] == 'X') {
          a[i] = a[i] | (1 << j);
        }
      }
    }
    cnt = 0;
    for (int i = 1; i <= n; i++) {
      // 两个完全相同的程序，最少要间隔多少时间片 i 启动，才不会发生资源冲突
      if (ok(a, i)) {

        delay[cnt] = i;
        cnt++;
      }
    }

    dfs(a, 1, n);
    printf("%d\n", ans);
  }
  return 0;
}