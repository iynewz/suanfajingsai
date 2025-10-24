// learn from https://vjudge.net/problem/UVA-1572
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
vector<vector<int>> adj; // 邻接表
const int NODE_COUNT = 52;

int getId(char c1, char c2)
{
    return (c1 - 'A') * 2 + ((c2 == '+') ? 0 : 1);
}

void connect(char a1, char a2, char b1, char b2)
{
    if (a1 == '0' || b1 == '0')
    {
        return;
    }
    int u = getId(a1, a2) ^ 1; // opposite
    int v = getId(b1, b2);
    adj[u].push_back(v);
}

bool bfs()
{
    int indegree[NODE_COUNT] = {0};
    int num = 0;
    for (int i = 0; i < NODE_COUNT; i++)
    {
        for (auto v : adj[i])
        {
            indegree[v]++; // 统计各点入度
        }
    }
    queue<int> q;
    for (int i = 0; i < NODE_COUNT; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        num++;
        for (auto v : adj[u])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    return num != NODE_COUNT; // 1: 有环 0: 无环
}

int n;
int main()
{
    while (scanf("%d", &n) == 1)
    {
        adj.clear();
        adj.resize(NODE_COUNT); // 初始化
        char s[8 + 1];
        for (int i = 0; i < n; i++)
        {
            scanf("%s ", s);

            for (int i = 0; i < 4; i++)
            { // 考虑旋转翻转
                for (int j = 0; j < 4; j++)
                    if (i != j)
                        connect(s[i * 2], s[i * 2 + 1], s[j * 2], s[j * 2 + 1]); // 构建有向图
            }
        }
        int has_loop = bfs();
        printf("%s\n", has_loop ? "unbounded" : "bounded");
    }
    return 0;
}