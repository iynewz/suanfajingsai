#include <stdio.h>

int main() {
    int n, m, case_num = 1;
    while (scanf("%d%d", &n, &m) == 2 && !(n == 0 && m == 0)) {
        double s = 0.0;
        for (long long i = n; i <= m; i++) {  // 使用 long long 避免溢出
            s += 1.0 / (i * i);
        }
        printf("Case %d: %.5f\n", case_num++, s);  // 修正格式字符串
    }
    return 0;
}