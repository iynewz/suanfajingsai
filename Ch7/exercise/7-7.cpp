// 埃及分数问题
// TLE
#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;
typedef long long LL;
int a, b, k;
int maxd;
const int maxn = 1000;
LL answer[maxn];
LL best_answer[maxn];
set<int> s;
int kase = 0;

LL dfs_cnt = 0;

// 返回最小的正整数 c，使得 1/c <= a/b
LL first(LL a, LL b) { return b / a + 1; }
int is_better() { // 判断当前是否比答案更优
  for (int d = maxd; d >= 0; d--) {
    if (answer[d] != best_answer[d]) {
      return best_answer[d] == -1 || answer[d] < best_answer[d];
    }
  }
  return false;
}

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
/*
d - 当前深度
from - 分母不能小于 from
aa - 剩余分数之和恰好为 aa/bb
bb -
*/
bool dfs(int d, LL from, LL aa, LL bb) {
  dfs_cnt++;
  if (dfs_cnt > 1e7)
    return false; // 人为截断

  if (d == maxd) {
    if (bb % aa != 0) {
      return false;
    }
    if (s.count(bb / aa)) { // bb/aa 不能作为分母
      return false;
    } else {
      answer[d] = bb / aa;
      if (is_better()) {
        memcpy(best_answer, answer, sizeof(answer));
      }
      return true;
    }
  }
  bool ok = false;
  from = max(from, first(aa, bb));

  for (;; from++) {
    // 如果(maxd-d+1)*1/from <
    // aa/bb，证明后面无法凑出aa/bb，做了工作也是徒劳，可以剪枝了
    if (s.count(from)) {
      continue;
    }
    if (bb * (maxd - d + 1) <= aa * from) {
      break;
    }
    answer[d] = from;

    LL bb2 = bb * from;
    LL aa2 = aa * from - bb;

    LL g = gcd(aa2, bb2); // 通分
    aa2 /= g;
    bb2 /= g;
    if (dfs(d + 1, from + 1, aa2, bb2)) {
      ok = true;
    }
  }
  return ok;
}
void print_ans() {

  printf("Case %d: %d/%d=", ++kase, a, b);

  for (int i = 0;; i++) {
    if (best_answer[i] < 0) {
      break;
    }
    if (i == 0) {
      printf("1/%lld", best_answer[i]);
    } else {
      printf("+1/%lld", best_answer[i]);
    }
  }

  printf("\n");
}

int main() {
  int T;

  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &a, &b, &k);
    s.clear(); // 不能漏了
    while (k--) {
      int tmp;
      scanf("%d", &tmp);
      s.insert(tmp);
    }
    for (maxd = 1;; maxd++) {
      memset(best_answer, -1, sizeof(best_answer));
      memset(answer, -1, sizeof(answer));
      if (dfs(0, first(a, b), a, b)) {
        print_ans();
        break;
      }
    }
  }

  return 0;
}