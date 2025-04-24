#include<stdio.h>
int  main()
{
    int n, S = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int factorial = 1;
        int j = i;
        while(j > 0) {
            factorial *= j;
            j --;
        }
        S += factorial;
    }
    printf("%d\n", S % 1000000);
    return 0;
}