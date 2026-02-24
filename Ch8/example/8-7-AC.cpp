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
    cin >> n;
    int ans = 0;
    int L = 0;
    set<int> s;

    for (int R = 0; R < n; R++) { // [L, R]
      cin >> A[R];
      // cout << "A[R]" << A[R] << endl;
      while (s.count(A[R])) {
        s.erase(A[L]);
        L++;
      }
      s.insert(A[R]);
      ans = max(R - L + 1, ans);
    }
    cout << ans << endl;
  }

  return 0;
}