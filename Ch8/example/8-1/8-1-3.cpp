// 最大连续和(2.1)
// 当 j 确定时，“S[j]-S[i-1]最大”
// 相当于“S[i-1]最小”。因此只需要扫描一次数组，维护“目前遇到过的最小 S”即可。
#include <iostream>
#include <vector>
using namespace std;
using namespace chrono;

int calculate(int n, const vector<int> &A) {
  vector<long long> S(n);
  long long prefix = 0;    // 当前 S[j]
  long long minPrefix = 0; // min{S[-1], S[0], ..., S[j-1]}
  long long best = A[0];
  for (int j = 0; j < n; j++) {
    prefix += A[j];
    best = max(best, prefix - minPrefix);
    minPrefix = min(minPrefix, prefix);
  }
  return best;
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
