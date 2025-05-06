#include <stdio.h>

int main() {
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int count[10] = {0}; // 初始化计数数组
        for (int i = 1; i <= n; i++) { // 从1开始处理到n
            int curr = i;
            while (curr > 0) {
                count[curr % 10]++; // 更新当前位的计数
                curr /= 10;
            }
        }
        for (int i = 0; i < 10; i++) // 输出结果
            printf("%d%c", count[i], i < 9 ? ' ' : '\n');
    }
    return 0;
}