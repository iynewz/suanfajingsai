#include <iostream>
using namespace std;

int n, Q; // 数组长度和操作次数
int a[8000 + 5];
int b[8000 + 5];

void init()
{
    for (int i = 1; i <= n; i++)
    {
        a[i] = b[i];
    }
}
void sort(int x)
{
    int tmp = x;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j >= 2; j--)
        {
            if (a[j] < a[j - 1])
            {
                swap(a[j], a[j - 1]);
                if (j - 1 == tmp)
                    tmp = j; // 原来在j-1的元素移动到j
                else if (j == tmp)
                    tmp = j - 1; // 原来在j的元素移动到j-1
            }
        }
    }
    cout << tmp << endl;
}

int main()
{
    cin >> n >> Q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i]; // 初始化b数组
    }
    for (int i = 0; i < Q; i++)
    {
        int op, x, v;
        cin >> op;
        if (op == 1)
        {
            cin >> x >> v;
            a[x] = b[x] = v; // 同步修改a和b
        }
        else
        {
            cin >> x;
            sort(x);
        }
    }
    return 0;
}