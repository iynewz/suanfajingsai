#include<stdio.h>
#include<math.h>
int main()
{
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            int n = a * 1000 + a * 100 + b * 10 + b;
            int m = floor(sqrt(n));
            if (m * m == n) {
                printf("m: %d\nn: %d\n", m, n);
            }
        }
    }
    return 0;
}