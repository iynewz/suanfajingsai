#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 100 + 5;

struct Building
{
    int id;
    double x, y, w, d, h;
    bool operator<(const Building &rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
} b[maxn];

int building_count;
double x[2 * maxn];

bool cover(int i, double mx)
{
    return b[i].x <= mx && b[i].x + b[i].w >= mx;
}

// 判断建筑物i在x=mx处是否可见
bool visible(int i, double mx)
{
    if (!cover(i, mx))
        return false;
    for (int k = 0; k < building_count; k++)
        if (b[k].y < b[i].y && b[k].h >= b[i].h && cover(k, mx))
            return false;
    return true;
}

int main()
{
    int case_num = 0;
    while (cin >> building_count && building_count != 0)
    {
        for (int i = 0; i < building_count; i++)
        {
            scanf("%lf%lf%lf%lf%lf", &b[i].x, &b[i].y, &b[i].w, &b[i].d, &b[i].h);
            x[2 * i] = b[i].x;
            x[2 * i + 1] = b[i].x + b[i].w; // 成对记录每个建筑物的左右边界横坐标
            b[i].id = i + 1;
        }
        sort(b, b + building_count);
        sort(x, x + 2 * building_count);
        int m = unique(x, x + building_count * 2) - x; // 唯一元素的数量

        if (case_num++)
            printf("\n");
        cout << "For map #" << case_num << ", the visible buildings are numbered as follows:\n"
             << b[0].id;

        // 判断一个矩形的各个线段区间是否会被挡住
        for (int i = 1; i < building_count; i++) // 当前矩形是b[i]
        {
            bool curr_visible = false;
            for (int j = 0; j < m - 1; j++)
            {
                if (visible(i, (x[j] + x[j + 1]) / 2))
                {
                    curr_visible = true;
                    break; //
                }
            }
            if (curr_visible)
            {
                printf(" %d", b[i].id);
            }
        }
        printf("\n");
    }
    return 0;
}
