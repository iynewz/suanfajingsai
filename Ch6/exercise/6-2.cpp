#include <cstdio>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    int tree = 1;

    while (scanf("%d", &n) == 1 && n)
    {
        vector<int> x(n);
        for (int i = 0; i < n; i++)
        {
            char s[3];
            scanf("%s", s);
            x[i] = s[1] - '0'; // 1-based
        }

        char leaf[200];
        scanf("%s", leaf);

        printf("S-Tree #%d:\n", tree++);

        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            char query[10];
            scanf("%s", query);

            int val = 0;
            for (int j = 0; j < n; j++)
            {
                int var = x[j] - 1;
                val = val * 2 + (query[var] - '0');
            }

            printf("%c", leaf[val]);
        }
        printf("\n\n");
    }
    return 0;
}
