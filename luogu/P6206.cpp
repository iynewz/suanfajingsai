#include <stdio.h>

int main()
{
    int count = 0;
    long long n;
    scanf("%lld", &n);
    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n = n / 2;
        }
        else
        {
            n = n * 3 + 1;
        }
        count++;
    }
    printf("%d\n", count);
    return 0;
}