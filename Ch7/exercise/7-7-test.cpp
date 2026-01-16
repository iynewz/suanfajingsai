// author: One_Zzz
// https://www.luogu.com.cn/article/v6fyi61h
#include <stdio.h>
#include <string.h>
#include <unordered_set> // unordered_set 其实只是哈希实现set，功能相同，没有排序
#include <vector>
#define int long long
const int &max2(const int &a, const int &b) { return a > b ? a : b; }
const int &min2(const int &a, const int &b) { return a < b ? a : b; }
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
inline int read() {
  register int x = 0;
  register char c = getchar();
  for (; c < '0' || c > '9'; c = getchar())
    ;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = x * 10 + (c ^ '0');
  return x;
}
std::unordered_set<int> s; // 保存q数组，使用.count(x)避免q中出现x
int dep;                   // 当前深度
int n, m, k, a[10001], res[10001];
// a:当前的a,res:答案
bool good() { // 判断当前是否比答案更优
  for (int i = dep; i >= 0; --i)
    if (a[i] != res[i])
      return !res[i] || a[i] < res[i];
  return false;
}
bool dfs(int d, int x, int y, int last) {
  if (d == dep) { // 搜完了
    if (y % x)
      return false; // 如果剩下不是1/(y/x)，返回
    if (s.count(y / x))
      return false; // 如果q中出现了
    a[d] = y;       // 记录答案
    if (good()) {   // 如果更优，更新答案
      for (int i = 0; i <= dep; ++i)
        res[i] = a[i];
    }
    return true;
  }
  bool flg = false; // 是否找到
  for (int i = max2(last + 1, y / x + 1);; ++i) {
    if (s.count(i))
      continue; // 出现过就跳过
    if (y * (dep - d + 1) <= i * x)
      break; // 剪枝，由于判断的是两个分数大小，所以可以乘上两个分母
    a[d] = i; // 记录i
    // 计算 x/y-1/i，使用通分，答案=y*i/x*i-y
    int newx = x * i - y, newy = y * i;
    int GCD = gcd(newx, newy); // 除以gcd
    newx /= GCD, newy /= GCD;
    flg |= dfs(d + 1, newx, newy, i);
  }
  return flg; // 返回是否找到
}
bool iddfs() {
  for (dep = 1;; ++dep) {       // 枚举深度
    memset(res, 0, sizeof res); // 每个深度都要清空答案
    if (dfs(0, n, m, m / n))
      return true; // 找到了赶紧走！
  }
}
#undef int
int main() {
  int T = read(), Case = 0;
  while (T--) {
    n = read(), m = read(), k = read();
    s.clear();
    for (int i = 1; i <= k; ++i)
      s.insert(read()); // 插入set
    iddfs();            // IDDFS主体函数
    // 毒瘤输出
    printf("Case %lld: %lld/%lld=1/%lld", ++Case, n, m, res[0]);
    for (int i = 1; i <= dep; ++i)
      printf("+1/%lld", res[i]);
    printf("\n");
  }
  return 0;
}
