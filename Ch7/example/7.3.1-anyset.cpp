#include <cstdio>
#include <algorithm>

// 打印所有子集：A 存放的是索引
void print_subset(int n, int* A, int cur, int* S) {
    // 打印当前子集（通过 A[] 映射到 S[]）
    for (int i = 0; i < cur; i++) {
        printf("%d ", S[A[i]]);
    }
    printf("\n");

    // 决定下一个元素的最小可选索引
    int s = cur ? A[cur - 1] + 1 : 0;

    // 从 s..n-1 继续向下构造
    for (int i = s; i < n; i++) {
        A[cur] = i;
        print_subset(n, A, cur + 1, S);
    }
}

int main() {
    int S[] = {4, 3, 2, 1, 9};// 原始集合
    int n = sizeof(S) / sizeof(S[0]);

    int A[100];  // 用来存放子集的下标
    print_subset(n, A, 0, S);

    return 0;
}
