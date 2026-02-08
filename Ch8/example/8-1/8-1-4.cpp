// 最大连续和(3)
// 分治
#include <iostream>
#include <vector>
using namespace std;
using namespace chrono;

long long maxSubarray(int l, int r, const vector<int> &A) {
  if (l == r)
    return A[l];

  int mid = (l + r) / 2;

  long long leftBest = maxSubarray(l, mid, A);
  long long rightBest = maxSubarray(mid + 1, r, A);

  long long sum = 0, leftSuffix = LLONG_MIN;
  for (int i = mid; i >= l; i--) {
    sum += A[i];
    leftSuffix = max(leftSuffix, sum);
  }

  sum = 0;
  long long rightPrefix = LLONG_MIN;
  for (int i = mid + 1; i <= r; i++) {
    sum += A[i];
    rightPrefix = max(rightPrefix, sum);
  }

  long long crossBest = leftSuffix + rightPrefix;

  return max({leftBest, rightBest, crossBest});
}

int main() {
  for (int n : {2000, 4000, 8000}) {
    vector<int> A(n, 1);

    auto start = high_resolution_clock::now();
    long long ans = maxSubarray(0, n - 1, A);
    auto end = high_resolution_clock::now();
    double t = duration<double>(end - start).count();
    cout << "n = " << n << ", time = " << t << " s\n";
  }
}
