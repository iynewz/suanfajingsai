// Ancient Cipher, UVa 1339
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_LEN 26

int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b; // 写得对吗，请解释这一行
}

int main() {
    char a[101], b[101];
    int cnt_a[MAX_LEN];
    int cnt_b[MAX_LEN];
    char c;
    while (scanf("%s %s", a, b) == 2) {
        memset(cnt_a, 0, sizeof(cnt_a));
        memset(cnt_b, 0, sizeof(cnt_b));
        int len_a = strlen(a);
        int len_b = strlen(b);
        for (int i = 0; i < len_a; i++) {
            cnt_a[a[i] - 'A']++;
        }
        for (int j = 0; j < len_b; j++) {
            cnt_b[b[j] - 'A']++;
        }
        qsort(cnt_a, MAX_LEN, sizeof(cnt_a[0]), compare);
        qsort(cnt_b, MAX_LEN, sizeof(cnt_b[0]), compare);

        //比较是否一致
        int valid = 1;
        for (int i = 0; i < MAX_LEN; i++) {
            if (cnt_a[i] != cnt_b[i]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}