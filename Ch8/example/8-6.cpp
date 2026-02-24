// learn from
// https://github.com/aoapc-book/aoapc-bac2nd/blob/master/ch8/UVa1606.cpp
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int maxn = 1000 + 5;
struct Point {
  int x, y;
  double atan;
  bool operator<(const Point &rhs) const { return atan < rhs.atan; }
} points[maxn], new_p[maxn];

int color[maxn];
int n;

// B 在 A 的逆时针/共线
bool isLeft(const Point &A, const Point &B) {
  int AB = A.x * B.y - B.x * A.y;
  return AB >= 0;
}
int solve() {
  if (n <= 2) {
    return 2;
  }
  int ans = 0;

  for (int i = 0; i < n; i++) { // i 是当前 pivot

    int k = 0; // 除了当前 pivot 点以外的点的数量
    for (int j = 0; j < n; j++) {
      if (j == i) {
        continue;
      }
      new_p[k].x = points[j].x - points[i].x;
      new_p[k].y = points[j].y - points[i].y;
      if (color[j]) {
        new_p[k].x = -new_p[k].x;
        new_p[k].y = -new_p[k].y;
      }
      new_p[k].atan = atan2(new_p[k].y, new_p[k].x);
      k++;
    }
    sort(new_p, new_p + k);

    int L = 0;
    int R = 0;
    int cnt = 2;
    while (L < k) {
      if (R == L) {
        R = (R + 1) % k;
        cnt++;
      }
      while (R != L && isLeft(new_p[L], new_p[R])) {
        R = (R + 1) % k;
        cnt++;
      }
      cnt--;
      L++;
      ans = max(ans, cnt);
    }
  }
  return ans;
}
int main() {
  while (cin >> n && n) {
    for (int i = 0; i < n; i++) {
      cin >> points[i].x >> points[i].y >> color[i];
    }
    int ans = solve();
    cout << ans << endl;
  }
  return 0;
}