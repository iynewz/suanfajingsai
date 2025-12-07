// 埃及分数问题
#include <cstdio>
#include <cstring>
#include <queue>
#include <cctype>
using namespace std;
typedef long long LL;
int a, b;
int maxd;
const int maxn = 1000;
int answer[maxn];
int best_answer[maxn];

// find smallest int c, make 1/c >= a/b
int first(int a, int b)
{
    for (int c = 1;; c++)
    {
        if (a * c >= b)
        {
            return c;
        }
    }
}
int is_better(int d)
{
    for (; d >= 0; d--)
    {
        if (answer[d] != best_answer[d])
        {
            return best_answer[d] == -1 || answer[d] < best_answer[d];
        }
    }
    return false;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 剩余分数 aa/bb
bool dfs(int d, int from, LL aa, LL bb)
{
    if (d == maxd)
    {
        if (bb % aa != 0)
        {
            return false;
        }
        else
        {
            answer[d] = bb / aa;
            if (is_better(d))
            {
                memcpy(best_answer, answer, sizeof(answer));
            }
            return true;
        }
    }
    bool ok = false;
    from = max(from, first(aa, bb));

    for (;; from++)
    {
        // 如果(maxd-d+1)*1/from < aa/bb，证明后面无法凑出aa/bb，做了工作也是徒劳，可以剪枝了
        if (bb * (maxd - d + 1) <= aa * from)
        {
            break;
        }
        answer[d] = from;

        LL bb2 = bb * from;
        LL aa2 = aa * from - bb;

        int g = gcd(aa2, bb2); // 通分

        if (dfs(d + 1, from + 1, aa2 / g, bb2 / g))
        {
            ok = true;
        }
    }
    return ok;
}
void print_ans()
{

    printf("%d/%d=", a, b);

    for (int i = 0;; i++)
    {
        if (best_answer[i] < 0)
        {
            break;
        }
        printf("1/%d ", best_answer[i]);
    }

    printf("\n");
}

int main()
{
    while (scanf("%d %d", &a, &b) != EOF)
    {
        for (maxd = 1;; maxd++)
        {
            memset(best_answer, -1, sizeof(best_answer));
            memset(answer, -1, sizeof(answer));
            if (dfs(0, first(a, b), a, b))
            {
                print_ans();
                break;
            }
        }
    }
    return 0;
}