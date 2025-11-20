#include <cstdio>

void print_subset(int n, int *A, int cur)
{
    // 打印当前子集
    for (int i = 0; i < cur; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    // s = 当前元素的最小可能编号
    int s = cur ? A[cur - 1] + 1 : 0;
    // 枚举下一个可能的元素
    for (int i = s; i < n; i++)
    {
        A[cur] = i;
        print_subset(n, A, cur + 1);
    }
}

int main()
{
    int n = 3;
    int A[100];
    print_subset(n, A, 0);
    return 0;
}
