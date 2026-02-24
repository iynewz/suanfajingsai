// 求一个数组中最长的不含重复元素的连续子数组长度

#include <algorithm>
#include <iostream>
#include <ostream>
#include <set>
using namespace std;
const int maxn = 1000000 + 5;
int A[maxn];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    int ans = 0;
    cin >> n;
    int L = 0;
    set<int> s;

    for (int R = 0; R < n; R++) { // [L, R]
      cin >> A[R];
      cout << "A[i]" << A[R] << endl;
      if (s.count(A[R]) == 0) {
        s.insert(A[R]);
        cout << "L, R: " << L << " " << R << endl;
      } else {
        // L 增加到让第一个 A[R] 排除在 set 之外 ⬅️ ❌ 这个逻辑错了，应该是只要
        // set 里还存在 A[R]，就继续删。
        while (A[L] != A[R]) {
          s.erase(A[L]);
          L++;
        }

        s.erase(A[L]);
        L++;
      }
      ans = max(R - L + 1, ans);
    }
    cout << ans << endl;
  }

  return 0;
}