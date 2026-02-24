#include <iostream>
using namespace std;
int main() {
  int n;
  while (cin >> n && n) {
    long long ans = 0;
    long long perfix = 0;
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      perfix += a;
      ans += abs(perfix);
    }
    cout << ans << endl;
  }

  return 0;
}