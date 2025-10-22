#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;
const int maxn = 1000 + 5;
const int ALPHA = 26;
vector<int> adj[ALPHA]; // 邻接表
bool used[ALPHA];       // 字母是否出现过
int in_deg[ALPHA];      // 入度
int out_deg[ALPHA];     // 出度
bool visited[ALPHA];

int T, N;

void init()
{
    for (int i = 0; i < ALPHA; i++)
    {
        adj[i].clear();
    }
    memset(used, 0, sizeof(used));
    memset(in_deg, 0, sizeof(in_deg));
    memset(out_deg, 0, sizeof(out_deg));
}

void dfs(int u)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v);
        }
    }
}

bool isConnected()
{
    int start = -1;
    for (int i = 0; i < ALPHA; i++)
    {
        if (used[i])
        {
            start = i;
            break;
        }
    }
    if (start == -1)
    {
        return true;
    }
    memset(visited, 0, sizeof(visited));
    dfs(start);

    for (int i = 0; i < ALPHA; i++)
    {
        if (used[i] && visited[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        init();
        scanf("%d", &N);
        char word[maxn];

        while (N--)
        {
            scanf("%s", word);
            int len = strlen(word);
            int u = word[0] - 'a';
            int v = word[len - 1] - 'a';
            adj[u].push_back(v);
            out_deg[u]++;
            in_deg[v]++;
            used[u] = true;
            used[v] = true;
        }

        bool hasEulerPath = false;

        if (isConnected())
        {
            int startNode = 0;
            int endNode = 0;
            for (int i = 0; i < ALPHA; i++)
            {
                if (used[i])
                {
                    int diff = out_deg[i] - in_deg[i];
                    if (diff == 1)
                    {
                        startNode++;
                    }
                    else if (diff == -1)
                    {
                        endNode++;
                    }
                    else if (diff != 0)
                    {
                        startNode = 3;
                        break;
                    }
                }
            }
            hasEulerPath = (startNode == 0 && endNode == 0) || (startNode == 1 && endNode == 1);
        }

        if (hasEulerPath)
        {
            printf("Ordering is possible.\n");
        }
        else
        {
            printf("The door cannot be opened.\n");
        }
    }
    return 0;
}