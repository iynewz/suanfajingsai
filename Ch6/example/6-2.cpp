//UVA 514，但 udebug 没过
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

const int maxn = 1000 + 5;
int target[maxn];

void init()
{
    for (int i = 0; i < maxn; i++)
    {
        target[i] = 0;
    }
}

int main()
{
    int N;
    while (scanf("%d", &N) == 1 && N)
    {
        stack<int> s;

        while (1)
        {
            init();
            scanf("%d", &target[1]);
            if (target[1] == 0)
            {
                break;
            }

            for (int i = 2; i <= N; i++)
            {
                scanf("%d", &target[i]);
            }

            int A = 1, B = 1;
            int ok = 1;
            while (B <= N)
            {
                if (A == target[B])
                {
                    A++;
                    B++;
                }
                else if (!s.empty() && s.top() == target[B])
                {
                    s.pop();
                    B++;
                }
                else if (A <= N)
                {
                    s.push(A);
                    A++;
                }
                else
                {
                    ok = 0;
                    break;
                }
            }
            printf("%s\n", ok ? "Yes" : "No");
        }
        printf("\n");
    }

    return 0;
}