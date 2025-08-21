// CSPJ 2020 - 第 20 题
#include <iostream>

using namespace std;

const int MAXN = 5000;
int n, m;
struct segment
{
    int a, b;
} A[MAXN];

void sort() // 排序
{
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n; j++)
            if (A[j].a < A[j - 1].a) // 1 左端点从小到大排序
            {
                segment t = A[j];
                A[j] = A[j - 1]; // 2
                A[j - 1] = t;
            }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> A[i].a >> A[i]・b;
    sort();    // 按左端点 a 从小到大排序
    int p = 1; // 当前有效线段的末尾位置
    for (int i = 1; i < n; i++)
        if (A[i].b > A[p - 1].b) // 3 保留右端点更大的线段，去掉被完全覆盖的线段
            A[p++] = A[i];
    n = p; // 更新有效线段数量
    int ans = 0, r = 0;
    int q = 0;
    while (r < m)
    {
        while (q + 1 < n && A[q + 1].a <= r) // 4
            q++;
        r = max(r, A[q].b); // 5
        ans++;
    }
    cout << ans << endl;
    return 0;
}
