// Repeating Decimals, UVa202
#include<stdio.h>
#include<string.h>

#define MAX_DIGIT 3005

int main() {
    int a, b;
    int remaining[MAX_DIGIT] = {0}; // remaining[a] -> a 作为余数第一次出现的位置
    int frac[MAX_DIGIT];
    int is_first_case = 1;

    while (scanf("%d %d", &a, &b) == 2) {

        memset(remaining, -1, sizeof(remaining));
        memset(frac, 0, sizeof(frac));

        printf("%d/%d = ", a, b);
    
        int integer = a / b;
        printf("%d.", integer);
        int i = 0;

        a = a % b;
        for (; a != 0 && remaining[a] == -1; i++) { //还没整除，且循环节还没出现
            remaining[a] = i;
            a *= 10;
            frac[i] = a / b;
            a = a % b;
        }

        if (a == 0) {
            for (int j = 0; j < i; j++) {
                printf("%d", frac[j]);
            }
            printf("(0)\n");
            printf("   1 = number of digits in repeating cycle\n");
        } else {
            int start = remaining[a];
            int end = i;
            int len = end - start;

            for (int j = 0; j < start; j++) {
                printf("%d", frac[j]);
            }

            printf("(");

            for (int j = start; j < end; j++) {
                printf("%d", frac[j]);
                if (end > 50 && j + 1 == 50) {
                    printf("...");
                    break;
                }
            }

            printf(")\n");

            printf("   %d = number of digits in repeating cycle\n", len);
        }
         puts("");
    }
    return 0;
}