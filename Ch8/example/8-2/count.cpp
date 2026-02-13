#include <iostream>
using namespace std;

long long cnt = 0; // 逆序对计数，必须用 long long（最大约 5×10^11）

void merge_sort(int *A, int x, int y, int *T) {
  if (y - x > 1) {
    int m = x + (y - x) / 2;
    int p = x, q = m, i = x;
    merge_sort(A, x, m, T);
    merge_sort(A, m, y, T);
    while (p < m || q < y) {
      if (q >= y || (p < m && A[p] <= A[q])) {
        T[i++] = A[p++]; // 从左半取
      } else {
        T[i++] = A[q++]; // 从右半取
        // 左半部分从p到m-1的所有元素都比A[q-1]大，且都在它左边
        cnt += (m - p);
      }
    }
    for (i = x; i < y; i++) {
      A[i] = T[i]; // 这样上一层递归拿到的 A 就是有序的，可以继续向上合并。
    }
  }
}

int main() {
  int A[4] = {3, 1, 4, 2};
  int T[4];
  merge_sort(A, 0, 4, T);
  for (int i : A) {
    cout << i << " ";
  }
  printf("\n cnt: %lld\n", cnt);

  return 0;
}