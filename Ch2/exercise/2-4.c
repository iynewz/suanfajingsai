#include<stdio.h>
int main() {
    int n, m;
    while(scanf("%d%d", &n, &m)==2 && !(n == 0 && m == 0)) {
        double s = 0.0;
        for(int i = n; i <= m; i++) {
            s += (1.0 / i) * (1.0 / i);
        }
        printf("Case xx: %.5f\n", s);
    }
    return 0;
}