// https://www.luogu.com.cn/problem/solution/UVA12333
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int maxsiz = 50;
const int inf = 2e9;
int T, l, pre[maxn];
char s[maxn];
struct bigint
{
    int a[maxsiz + 1];
    void dis()
    {
        for (int i = 0; i < maxsiz; i++)
            a[i] = a[i + 1];
        a[maxsiz] = 0;
    }
    bigint operator+(bigint x)
    {
        bigint ans;
        int r = 0;
        if (a[maxsiz] || x.a[maxsiz])
            this->dis(), x.dis();
        for (int i = 0; i <= maxsiz; i++)
            ans.a[i] = r + a[i] + x.a[i], r = ans.a[i] / 10, ans.a[i] %= 10;
        return ans;
    }
    void output()
    {
        int i;
        for (i = maxsiz; !a[i]; i--)
            ;
        for (; i >= 0; i--)
            printf("%d", a[i]);
        printf("\n");
    }
} f[maxn];

struct node
{
    int v;
    node *c[10];
    node()
    {
        v = inf;
        for (int i = 0; i < 10; i++)
            c[i] = NULL;
    }
} trie;

void insert(bigint x, int cur)
{
    int i;
    node *now = &trie;
    for (i = maxsiz; !x.a[i]; i--)
        ;
    for (; i >= 0; i--)
    {
        if (now->c[x.a[i]] == NULL)
            now->c[x.a[i]] = new node;
        now = now->c[x.a[i]];
        now->v = min(now->v, cur);
    }
}
int prev(int x[])
{
    node *now = &trie;
    for (int i = 0; i < l; i++)
    {
        if (now->c[x[i]] == NULL)
            return -1;
        now = now->c[x[i]];
    }
    return now->v;
}
int main()
{
    f[0].a[0] = 1;
    f[1].a[0] = 1;
    insert(f[0], 0);
    for (int i = 2; i < 100000; i++)
        f[i] = f[i - 1] + f[i - 2], insert(f[i], i);
    scanf("%d", &T);
    for (int t = 1; t <= T; t++)
    {
        scanf("%s", s);
        l = strlen(s);
        for (int i = 0; i < l; i++)
            pre[i] = s[i] - '0';
        printf("Case #%d: %d\n", t, prev(pre));
    }
    return 0;
}
