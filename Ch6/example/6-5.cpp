#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 100000 + 5;

int l[maxn];
int r[maxn];

int n, m;
int case_num = 0;

void init(int n)
{
    for (int i = 1; i <= n; i++) // build lined list
    {
        l[i] = i - 1;
        r[i] = (i + 1) % (n + 1);
    }
    r[0] = 1;
    l[0] = n;
}

void link(int a, int b)
{
    r[a] = b;
    l[b] = a;
}

int main()
{
    while (cin >> n >> m)
    {
        init(n);

        int op, x, y;
        bool inverse_flag = 0;
        while (m--)
        {
            cin >> op;
            if (op == 4)
            {
                inverse_flag = !inverse_flag;
            }
            else
            {
                cin >> x >> y;
                if (op == 3 && r[y] == x)
                {
                    swap(x, y);
                };
                if (op != 3 && inverse_flag)
                {
                    op = 3 - op;
                }
                if (op == 1 && x == l[y]) // 忽略，第一次 WA 错在忘记忽略
                {
                    continue;
                }

                if (op == 2 && x == r[y]) // 忽略
                {
                    continue;
                }

                int lx = l[x], rx = r[x], ly = l[y], ry = r[y];
                if (op == 1)
                {
                    link(lx, rx);
                    link(ly, x);
                    link(x, y);
                }
                else if (op == 2)
                {
                    link(lx, rx);
                    link(y, x);
                    link(x, ry);
                }
                else if (op == 3)
                {
                    if (r[x] == y)
                    { // 相邻
                        link(lx, y);
                        link(y, x);
                        link(x, ry);
                    }
                    else // 不相邻
                    {
                        link(lx, y);
                        link(y, rx);
                        link(ly, x);
                        link(x, ry);
                    }
                }
            }
        }
        long long ans = 0;
        int tmp = 0;
        for (int i = 1; i <= n; i++)
        {
            tmp = r[tmp];
            if (i % 2 == 1)
            {
                ans += tmp;
            }
        }
        if (inverse_flag && n % 2 == 0)
        {
            ans = (long long)n * (n + 1) / 2 - ans;
        }
        cout << "Case " << ++case_num << ": " << ans << endl;
    }
    return 0;
}