#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 7 * 7 + 5;
int a[maxn] = {0};
vector<int> record; // 开多大？题目没说
int target;         // 1, 2, 3
int maxd;

vector<int> center = {17, 18, 19, 24, 26, 31, 32, 33}; // center cell index
//
//              operation: A, B, C, D, E, F, G, H
//   opposite operation of 0, 1, 2, 3, 4, 5, 6, 7  其实也是有数学规律的，但打表也很清晰
vector<int> opposite_op = {5, 4, 7, 6, 1, 0, 3, 2};

int check_center()
{
    int target = a[center[0]];
    for (auto i : center)
    {
        if (a[i] != target)
        {
            return -1;
        }
    }
    return target;
}

bool read()
{
    scanf("%d", &a[3]);
    if (a[3] == 0)
    {
        return false;
    }
    scanf("%d %d %d", &a[5], &a[10], &a[12]);
    for (int i = 1; i <= 7; i++)
    {
        scanf("%d", &a[14 + i]);
    }
    scanf("%d %d", &a[24], &a[26]);
    for (int i = 1; i <= 7; i++)
    {
        scanf("%d", &a[28 + i]);
    }
    scanf("%d %d %d %d", &a[38], &a[40], &a[45], &a[47]);
    return true;
}

void test_print()
{
    for (int r = 1; r <= 7; r++)
    {
        for (int c = 1; c <= 7; c++)
        {
            printf("%d ", a[(r - 1) * 7 + c]);
        }
        printf("\n");
    }
}
int getH()
{
    int cnt[4] = {0};

    for (auto i : center)
    {
        cnt[a[i]]++;
    }
    int max_cnt = max({cnt[1], cnt[2], cnt[3]});
    return 8 - max_cnt;
}

void move(int op)
{
    switch (op)
    {
        int tmp;
    case 0:
        tmp = a[3];
        for (int i = 0; i <= 5; i++)
        {
            a[i * 7 + 3] = a[(i + 1) * 7 + 3];
        }
        a[45] = tmp;
        break;
    case 1:
        tmp = a[5];
        for (int i = 0; i <= 5; i++)
        {
            a[i * 7 + 5] = a[(i + 1) * 7 + 5];
        }
        a[47] = tmp;
        break;
    case 2:
        tmp = a[21];
        for (int i = 21; i >= 16; i--)
        {
            a[i] = a[i - 1];
        }
        a[15] = tmp;
        break;
    case 3:
        tmp = a[35];
        for (int i = 35; i >= 30; i--)
        {
            a[i] = a[i - 1];
        }
        a[29] = tmp;
        break;
    case 4:
        tmp = a[47];
        for (int i = 5; i >= 0; i--)
        {
            a[(i + 1) * 7 + 5] = a[i * 7 + 5];
        }
        a[5] = tmp;
        break;
    case 5:
        tmp = a[45];
        for (int i = 5; i >= 0; i--)
        {
            a[(i + 1) * 7 + 3] = a[i * 7 + 3];
        }
        a[3] = tmp;
        break;
    case 6:
        tmp = a[29];
        for (int i = 29; i <= 34; i++)
        {
            a[i] = a[i + 1];
        }
        a[35] = tmp;
        break;
    case 7:
        tmp = a[15];
        for (int i = 15; i <= 20; i++)
        {
            a[i] = a[i + 1];
        }
        a[21] = tmp;
        break;
    }
    return;
}

bool dfs(int op, int d) // op 是上一操作， d is current depth
{
    // 剪枝
    int h = getH();
    // printf("maxd: %d d: %d h : %d\n", maxd, d, h);
    if (h > maxd - d)
    {
        return false;
    }
    if (d == maxd)
    {
        target = check_center();
        if (target > 0)
        {
            return true;
        }
        else
            return false;
    }
    int tmp[maxn];
    memcpy(tmp, a, sizeof(a));
    vector<int> tmp_vec = record;
    for (int i = 0; i < 8; i++)
    {
        if (opposite_op[i] == op)
        {
            continue;
        }
        // execute operation
        move(i);

        record.push_back(i);

        if (dfs(i, d + 1))
        {
            return true;
        }
        memcpy(a, tmp, sizeof(tmp));
        record = tmp_vec;
    }
    return false;
}

int main()
{
    while (read())
    {
        // test_print();

        int same = check_center();
        if (same > 0)
        {
            printf("No moves needed\n%d\n", same);
            continue;
        }
        // IDA
        for (maxd = 1;; maxd++)
        {
            record.clear();

            if (dfs(-1, 0))
            {
                break;
            }
        }
        for (auto i : record)
        {
            printf("%c", 'A' + i);
        }
        printf("\n%d\n", target);
    }

    return 0;
}
