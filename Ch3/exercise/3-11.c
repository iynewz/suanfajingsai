//Kickdown, UVa1588
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1000

int main() {
    char a[MAX_LEN];
    char b[MAX_LEN];
    while (scanf("%s", a) == 1) {
        scanf("%s", b);
        int len_a = strlen(a);
        int len_b = strlen(b);
        // printf("%d %d\n", len_a, len_b);
        
        int min_len = len_a + len_b;

        for (int i = 0 - len_b; i < len_a; i++) {
            int pointer_a = i;
            int valid = 1;
            int j = 0;
            while (j < len_b) {
                
                int a_value, b_value = b[j] - '0';
                if (pointer_a >= len_a || pointer_a < 0) { // pointer_a 可能超过 a 的长度, 避免越界访问
                    a_value = 0;
                } else {
                    a_value = a[pointer_a] - '0';
                }

                if (a_value + b_value <= 3) {
                    j++;
                    pointer_a++;
                } else {

                    valid = 0;
                    break;
                }
            }
            if (valid) {
                // printf("--valid-- i : %d\n", i);
                int curr_len;
                if (i < 0) {
                    curr_len = (len_a + abs(i)) >= len_b ? len_a + abs(i) : len_b;
                } else {
                    curr_len = (len_b + i) >= len_a ? len_b + i : len_a;
                }
                if (curr_len < min_len) {
                    min_len = curr_len;
                }
                // printf("curr_len: %d\n", curr_len);
            }

        }
        printf("%d\n", min_len);

    }
    return 0;
    
}