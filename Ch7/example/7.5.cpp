// in progress
#include <iostream>
#include <cstring>
#include <set>

// 264137058
// 815736402
using namespace std;
typedef int State[9];
const int maxstate = 1000000;
State st[maxstate], goal;
int dist[maxstate];
set<int> vis;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
void init_look_up_table()
{
    vis.clear();
}
int try_to_insert(int s) // 避免一个节点访问多次
{
    int v = 0;
    for (int i = 0; i < 9; i++)
    {
        v = v * 10 + st[s][i];
    }
    if (vis.count(v))
    {
        return 0;
    }
    vis.insert(v);
    return 1;
}

int bfs()
{
    init_look_up_table();
    int front = 1;
    int rear = 2;
    while (front < rear)
    {
        State &s = st[front]; // 当前正在处理的 9 格子状态
        if (memcmp(s, goal, sizeof(s)) == 0)
        {
            return front; // st[front] 就是目标状态
        }
        int z;
        for (z = 0; z < 9; z++) // 找到空格序号
        {
            if (s[z] == 0)
            {
                break;
            }
        }
        // 0,1,2
        // 3,4,5
        // 6,7,8
        int x = z / 3; // 空格所在行和列
        int y = z % 3;
        for (int d = 0; d < 4; d++) // 遍历四个方向的移动
        {
            int newx = x + dx[d];
            int newy = y + dy[d];
            int newz = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3)
            {
                State &t = st[rear]; // 构造 rear 位置的节点，相当于往 queue 里 push back 一个节点
                memcpy(&t, &s, sizeof(s));
                t[newz] = s[z];
                t[z] = s[newz];
                dist[rear] = dist[front] + 1;
                if (try_to_insert(rear))
                {
                    rear++;
                }
            }
        }
        front++;
    }
    return 0;
}

int main()
{
    for (int i = 0; i < 9; i++)
    {
        cin >> st[1][i];
    }
    for (int i = 0; i < 9; i++)
    {
        cin >> goal[i];
    }
    int ans = bfs();
    if (ans > 0)
    {
        printf("%d\n", dist[ans]);
    }
    else
    {
        printf("-1\n");
    }
    return 0;
}