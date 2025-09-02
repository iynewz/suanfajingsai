#include <stdio.h>
#include <iostream>

#include <queue>
using namespace std;
int n;
int t[200000 + 5];
int visited[200000 + 5]; // 第一次我忽略了需要记录 visited。 start 不能完全保留信息。可能出现： 夹中间的一位被 push 进 q2 后重复打印的问题

struct Block
{
    int start;
    int end;
    int type; // 1 or 0
};
queue<Block> q, q2;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &t[i]);
    }
    t[n + 1] = !t[n];
    int si = 1;
    for (int i = 2; i <= n + 1; i++)
    {
        if (t[i] != t[i - 1])
        {
            q.push({si, i - 1, t[i - 1]});
            si = i;
        }
    }
    int cnt = n;
    while (cnt)
    {
        while (q.size())
        {
            Block curr = q.front();
            q.pop();
            if (curr.start > curr.end)
            {
                continue;
            }
            while (visited[curr.start])
            {
                curr.start++;
            }
            printf("%d ", curr.start);
            visited[curr.start] = 1;
            curr.start++;
            cnt--;
            if (curr.start <= curr.end)
            {
                // cout << "push to q2: " << curr.start << " " << curr.end << endl;
                q2.push(curr);
            }
        }
        printf("\n");
        while (q2.size())
        {
            Block first = q2.front();
            q2.pop();
            while (q2.size())
            {
                Block next = q2.front();
                if (first.type == next.type)
                {
                    first.end = next.end;
                    q2.pop();
                }
                else
                {
                    break;
                }
            }
            q.push(first);
        }
    }

    return 0;
}