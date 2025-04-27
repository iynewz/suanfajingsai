//Digit Generator, Uva1583
#include<stdio.h>
#include<string.h>
#define maxn 100005
int ans[maxn];

int main() {
    memset(ans, 0, sizeof(ans));
    for(int i = 1; i <= maxn; i++) {
        int x = i, y = i;

        while(x > 0) {
            y += x % 10;
            x = x / 10;
        }
        if(y < maxn && (ans[y] == 0 || i < ans[y]) ) {
            ans[y] = i;
        }
    }
    // printf("Printing ans array:\n");
    // for (int i = 1; i <= 100; i++) {
    //     printf("ans[%d] = %d\n", i, ans[i]);
    // }
    int d;
    while(scanf("%d", &d) == 1) {
        printf("%d\n", ans[d]);
    }
    return 0;
}