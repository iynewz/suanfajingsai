// g++ bench.cpp -O0 -std=c++17 -o bench
// ./bench n3

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using clk = chrono::high_resolution_clock;

/************ 三种算法 ************/

// O(n^3)
ll max_subarray_n3(const vector<int> &A) {
  int n = A.size();
  ll best = A[0];
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      ll sum = 0;
      for (int k = i; k <= j; k++) {
        sum += A[k];
      }
      best = max(best, sum);
    }
  }
  return best;
}

// O(n^2)（前缀和）
ll max_subarray_n2(const vector<int> &A) {
  int n = A.size();
  vector<ll> S(n + 1, 0);
  for (int i = 0; i < n; i++) {
    S[i + 1] = S[i] + A[i];
  }

  ll best = A[0];
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      best = max(best, S[j] - S[i - 1]);
    }
  }
  return best;
}

// O(n)（Kadane / 前缀最小值）
ll max_subarray_n1(const vector<int> &A) {
  ll best = A[0];
  ll cur = 0;
  for (int x : A) {
    cur = max((ll)x, cur + x);
    best = max(best, cur);
  }
  return best;
}

/************ Benchmark ************/

template <typename Func> double run(Func f, const vector<int> &A) {
  auto start = clk::now();
  volatile ll ans = f(A); // volatile 防止优化
  auto end = clk::now();
  chrono::duration<double> diff = end - start;
  return diff.count();
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << "Usage: ./bench [n1|n2|n3]\n";
    return 1;
  }

  string mode = argv[1];
  srand(1);

  vector<int> ns = {50, 100, 200, 400, 800, 1600, 3200, 6400};

  // 写 csv
  cout << "n,time\n";

  for (int n : ns) {
    vector<int> A(n);
    for (int i = 0; i < n; i++)
      A[i] = rand() % 200 - 100;

    double t;

    if (mode == "n3")
      t = run(max_subarray_n3, A);
    else if (mode == "n2")
      t = run(max_subarray_n2, A);
    else if (mode == "n1")
      t = run(max_subarray_n1, A);
    else {
      cerr << "Unknown mode\n";
      return 1;
    }

    cout << n << "," << t << "\n";
  }
}
