#include<stdio.h>
#include<time.h>
int  main()
{
    const int MOD = 1000000;
    int n, S = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int factorial = 1;
        int j = i;
        while(j > 0) {
            factorial = (factorial * j) % MOD;
            j --;
        }
        S = (S + factorial) % MOD;
    }
    printf("%d\n", S);
    printf("Time used = %.2f\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}