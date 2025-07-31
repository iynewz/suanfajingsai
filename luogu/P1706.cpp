#include <stdio.h>
// 按照字典序输出自然数 1 到 n 所有不重复的排列，即 n 的全排列，要求所产生的任一数字序列中不允许出现重复的数字。

int n;
int cnt = 0;
bool visit[10 + 5];
int ans[10 + 5];
bool isStart = true;
void printAns()
{
    if (!isStart)
    {
        printf("\n");
    }
    for (int i = 0; i < n; i++)
    {
        printf("%5d", ans[i]);
    }
    isStart = false;
}

void dfs(int k)
{
    if (cnt == n)
    {
        printAns();
    }
    for (int i = 1; i <= n; i++)
    {
        if (!visit[i])
        {
            visit[i] = true;
            ans[cnt++] = i;
            dfs(i);
            visit[i] = false;
            cnt--;
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0);
    return 0;
}