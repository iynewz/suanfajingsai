#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int maxn = 100 + 5;

int main()
{
    int n, m;
    while (cin >> n >> m && (n || m))
    {
        vector<int> graph[maxn];  // 邻接表
        int indegree[maxn] = {0}; // 入度数组
        vector<int> result;       // 存储拓扑排序结果

        // 读入约束关系
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v); // u -> v
            indegree[v]++;         // v的入度+1
        }

        // BFS 拓扑排序 - Kahn算法
        queue<int> q;

        // 1. 将所有入度为0的节点加入队列
        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // 2. BFS过程
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u); // 加入结果

            // 遍历u的所有邻接点
            for (int i = 0; i < graph[u].size(); i++)
            {
                int v = graph[u][i];
                indegree[v]--; // 邻接点入度-1

                // 如果入度变为0，加入队列
                if (indegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        // 输出结果
        for (int i = 0; i < result.size(); i++)
        {
            if (i > 0)
                cout << " ";
            cout << result[i];
        }
        cout << endl;
    }

    return 0;
}