#include<stdio.h>

int sum(int* begin, int* end) {
    // int *p = begin;
    int ans = 0;
    for(int *p = begin; p != end; p++) {
        ans += *p;
    }
    printf("%d\n", ans);
    return ans;
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    sum(a, a + 5);
    return 0;
}