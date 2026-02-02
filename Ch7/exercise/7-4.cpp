/**
习题 7-4 切断圆环链(Cutting Chains, ACM/ICPC World Finals 2000, UVa818)
learn from https://www.cnblogs.com/zyb993963526/p/6350198.html

*/
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>
using namespace std;
const int maxn = 15 + 5;
int n, a, b, ans;
int mapp[maxn][maxn];
int used[maxn];
int num = 0;

#define inf 1e8 + 7
bool tooManyLink(int bits) {
  // bits 是掩码，比如 00100，0 是没打开的。
  // bits & (1<<i) == false 就是找没打开的位
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    for (int j = 0; j < n; j++) {
      if ((bits & (1 << i)) == false && (bits & (1 << j)) == false &&
          mapp[i][j]) {
        cnt++;
        if (cnt > 2) {
          return true;
        }
      }
    }
  }
  return false;
}

bool dfs(int curr, int parent, int bits) { // 判断是否有回路存在
  used[curr] = 1;
  for (int i = 0; i < n; i++) {
    if (mapp[curr][i]) {
      if (i == parent || (bits & (1 << i))) {
        continue;
      }
      if (used[i]) {
        return true;
      }
      if (dfs(i, curr, bits)) {
        return true;
      };
    }
  }
  return false;
}

bool hasCycle(int bits) {
  memset(used, 0, sizeof(used));
  for (int i = 0; i < n; i++) {
    if (!used[i] && (bits & (1 << i)) == false) {
      num++;
      // 只对“当前状态下剩下的未打开圆环”做 DFS 遍历
      if (dfs(i, -1, bits)) {
        return true;
      }
    }
  }
  return false;
}

int calc(int bits) {
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (bits & (1 << i)) {
      cnt++;
    }
  }
  return cnt;
}

void solve() {
  ans = inf;
  for (int i = 0; i < (1 << n); i++) {
    // check this open state
    num = 0;

    if (tooManyLink(i)) {
      continue;
    }
    if (hasCycle(i)) {
      continue;
    }
    // open: 被“打开”的圆环数量
    // num: 在“未打开的圆环”组成的图中，有多少个连通分量
    int open = calc(i);
    if (num - 1 <= open) {
      ans = min(ans, open);
    }
  }
}

int main() {
  int kase = 0;
  while (scanf("%d", &n) != EOF && n) {
    memset(mapp, 0, sizeof(mapp));
    while (scanf("%d%d", &a, &b) != EOF && a != -1 && b != -1) {
      mapp[a - 1][b - 1] = 1;
      mapp[b - 1][a - 1] = 1;
    }
    solve();
    printf("Set %d: Minimum links to open is %d\n", ++kase, ans);
  }
}
