#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 200;
int sum[maxn];

void build(int pos)
{
    int v;
    cin >> v;
    if (v == -1)
    {
        return;
    }
    sum[pos] += v;
    build(pos - 1);
    build(pos + 1);
}

// 边读入边统计
bool init()
{
    memset(sum, 0, sizeof(sum));
    int v;
    cin >> v;
    if (v == -1)
    {
        return false;
    }
    int root_pos = maxn / 2;
    sum[root_pos] += v;
    build(root_pos - 1); // 左子树
    build(root_pos + 1); // 右子树
    return true;
}

int main()
{
    int kase = 0;
    while (init())
    {
        int p = 0;
        while (sum[p] == 0)
        {
            p++;
        }
        cout << "Case " << ++kase << ":\n"
             << sum[p++];
        while (sum[p] != 0)
        {
            cout << " " << sum[p++];
        }
        cout << "\n\n";
    }
    return 0;
}