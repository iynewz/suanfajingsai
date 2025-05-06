//Digit counting, Uva1225
#include<stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, i;
        scanf("%d", &n);
        int digit_0 = 0, digit_1 = 0, digit_2 = 0, digit_3 = 0, digit_4 = 0, digit_5 = 0, digit_6 = 0, digit_7 = 0, digit_8 = 0, digit_9 = 0;
        for(i = 0; i <= n; i++) {
            int curr = i;
            while(curr > 0) {
                int remainder = curr % 10;
                if(remainder == 0) digit_0++;
                if(remainder == 1) digit_1++;
                if(remainder == 2) digit_2++;
                if(remainder == 3) digit_3++;
                if(remainder == 4) digit_4++;
                if(remainder == 5) digit_5++;
                if(remainder == 6) digit_6++;
                if(remainder == 7) digit_7++;
                if(remainder == 8) digit_8++;
                if(remainder == 9) digit_9++;
                curr = curr/10;
            }
        }
        printf("%d %d %d %d %d %d %d %d %d %d\n", digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9);
    }
    return 0;
}