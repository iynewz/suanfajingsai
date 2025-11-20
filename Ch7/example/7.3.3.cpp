#include <cstdio>

void print_subset(int n, int s)
{
    for (int i = 0; i < n; i++)
    {
        if (s & (1 << i))
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main()
{
    int n = 5;
    for (int i = 0; i < (1 << n); i++)
    {
        print_subset(n, i);
    }
    return 0;
}
