
// learn from: https://wcr1996.com/2015/02/28/uva-11212-editing-a-book/
#include <cstdio>
#include <cstring>
using namespace std;
int n;
const int maxn = 9;
int a[maxn];
int maxd; // 剪切几次可完成排序

int h() // 后继错误的个数
{
    int cnt = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] + 1 != a[i + 1])
        {
            cnt++;
        }
    }
    if (a[n - 1] != n)
    {
        cnt++;
    }
    return cnt;
}

bool dfs(int d)
{
    int bad_cnt = h();
    if (bad_cnt > 3 * (maxd - d))
    {
        return false;
    }
    if (bad_cnt == 0)
    {
        return true;
    }
    int temp[maxn];      // save the original
    int after_cut[maxn]; // 存：剪掉后的剩余部分
    memcpy(temp, a, sizeof(a));
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++) // 区间 [i..j] 是剪下来的部分。
        {
            int cut_len = j - i + 1;
            int remain_len = n - cut_len;
            memcpy(after_cut, temp, sizeof(int) * i);                       // 构造剪切
            memcpy(after_cut + i, temp + j + 1, sizeof(int) * (n - j - 1)); // 记得 -1
            for (int k = 0; k <= remain_len; ++k)                           // 枚举粘贴的位置 k
            {
                if (i == k)
                {
                    continue; // 和原位置一样就没意义
                }
                // 构造粘贴后的 a:  c[0..k-1] + (剪下的段) + c[k..end]
                memcpy(a, after_cut, sizeof(int) * k);
                memcpy(a + k, temp + i, sizeof(int) * cut_len);
                memcpy(a + k + cut_len, after_cut + k, sizeof(int) * (remain_len - k));
                if (dfs(d + 1))
                {
                    return true;
                }
            }
        }
    }
    memcpy(a, temp, sizeof(a)); // 恢复
    return false;
}

int main()
{
    int t = 0;
    while (scanf("%d", &n) == 1 && n)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        for (maxd = 0;; maxd++)
        {
            if (dfs(0))
            {
                break;
            }
        }
        printf("Case %d: %d\n", ++t, maxd);
    }
    return 0;
}