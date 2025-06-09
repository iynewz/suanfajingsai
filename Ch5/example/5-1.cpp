// Where is the Marble ? UVa 10474
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 10005

int main()
{
    int case_number = 1;
    int n, query_count;
    int marbles[maxn];

    while (scanf("%d %d", &n, &query_count) == 2 && (n != 0 && query_count != 0))
    {
        printf("CASE# %d:\n", case_number++);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &marbles[i]);
        }
        sort(marbles, marbles + n);
        for (int i = 0; i < query_count; i++)
        {
            int q;
            scanf("%d", &q);
            int index = lower_bound(marbles, marbles + n, q) - marbles;
            if (index < n && marbles[index] == q)
            {
                printf("%d found at %d\n", q, index + 1);
            }
            else
            {
                printf("%d not found\n", q);
            }
        }
    }
    return 0;
}