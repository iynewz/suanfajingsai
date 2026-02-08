// 最大连续和(1)
#include <iostream>
#include <vector>
using namespace std;
using namespace chrono;

void calculate(int n, const vector<int> &A) {
  long long best = A[0];

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      int sum = 0;
      for (int k = i; k <= j; k++) {
        sum += A[k]; // 核心操作
      }
      if (sum > best)
        best = sum;
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
