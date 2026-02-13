#include <iostream>
using namespace std;
/*
index: [x, y)
 */
void merge_sort(int *A, int x, int y, int *T) {
  if (y - x > 1) {
    int m = x + (y - x) / 2;
    int p = x, q = m, i = x;
    // 递归分解：排序左半 [x,m) 和右半 [m,y)
    merge_sort(A, x, m, T);
    merge_sort(A, m, y, T);
    while (p < m || q < y) { // 只要左半或右半还有元素没处理完，就继续
      if (q >= y || (p < m && A[p] <= A[q])) {
        // 情况：右半已空，或者左半没空且左边元素更小，从左半取
        T[i++] = A[p++];
      } else {
        T[i++] = A[q++]; // 从右半取
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
  return 0;
}