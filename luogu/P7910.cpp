#include <iostream>
#include <algorithm>
using namespace std;

int n, Q;
struct node
{
    int nvalue, nid;
};
node a[8000 + 5];
int t[8000 + 5];

bool cmp(node a, node b)
{
    if (a.nvalue != b.nvalue)
    {
        return a.nvalue < b.nvalue;
    }
    return a.nid < b.nid;
}

int main()
{
    cin >> n >> Q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].nvalue;
        a[i].nid = i; // 保存原始下标
    }

    sort(a + 1, a + n + 1, cmp);

    // sort 之后，a[] 已经按 value 排序了。记录 新的下标 的顺序
    for (int i = 1; i <= n; i++)
    {
        t[a[i].nid] = i;
    }
    // a.nvalue : 6 8 1
    // a.nid.   : 1 2 3
    // 排序后。     1。6。8。 a
    // t[3] = 1, t[1] = 2, t[2] = 3

    for (int i = 0; i < Q; i++)
    {
        int op, x, v;
        cin >> op;
        if (op == 1) // 修改
        {
            cin >> x >> v;
            a[t[x]].nvalue = v;
            for (int j = 2; j <= n; j++)
            {
                if (cmp(a[j], a[j - 1]))
                {
                    swap(a[j], a[j - 1]);
                }
            }
            for (int j = n; 2 <= j; j--)
            {
                if (cmp(a[j], a[j - 1]))
                {
                    swap(a[j], a[j - 1]);
                }
            }
            for (int i = 1; i <= n; i++)
            {
                t[a[i].nid] = i;
            }
        }
        else
        {
            cin >> x;
            cout << t[x] << endl;
        }
    }
    return 0;
}