#include<stdio.h>
int main() {
    int a, b, c;
    int case_num = 0;
    while(scanf("%d%d%d", &a, &b, &c) == 3 && !(a == 0 && b == 0 && c == 0)) {
        case_num++;
        if (b == 0) {
            printf("Case %d: Division by zero is undefined\n", case_num);
            continue;
        }
        double ans = (double)a/b;
        printf("Case %d: %.*f\n", case_num, c, ans);

    }
    return 0;
}