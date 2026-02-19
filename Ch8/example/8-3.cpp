// Uva 1152
#include <iostream>
#include <unordered_map>

using namespace std;
const int maxn = 4000 + 5;
int A[maxn], B[maxn], C[maxn], D[maxn];
unordered_map<int, int> cnt; // sumAB, cnt

int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    cnt.clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int sumAB = A[i] + B[j];
        cnt[sumAB]++;
      }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int sumCD = -C[i] - D[j];
        auto search = cnt.find(sumCD);
        if (search != cnt.end()) {
          ans += search->second;
        }
      }
    }
    cout << ans << endl;
    if (kase != 0) {
      cout << "\n";
    }
  }
}