// 最大连续和(2)
#include <iostream>
#include <vector>
using namespace std;
using namespace chrono;

void calculate(int n, const vector<int> &A) {
  long long best = A[0];
  // long long S[n]; // 在 C++中，数组大小必须是编译时常量
  vector<long long> S(n);
  S[0] = A[0];

  for (int i = 1; i < n; i++) {
    S[i] = S[i - 1] + A[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      best = max(best, S[j] - S[i - 1]);
    }
  }
}

int main() {
  for (int n : {2000, 4000, 8000}) {
    vector<int> A(n, 1);

    auto start = high_resolution_clock::now();
    calculate(n, A);
    auto end = high_resolution_clock::now();
    double t = duration<double>(end - start).count();
    cout << "n = " << n << ", time = " << t << " s\n";
  }
}
