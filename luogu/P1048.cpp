#include <iostream>
using namespace std;

struct Node
{
    int t, w; // 采摘某株草药的时间和这株草药的价值
};

Node nodes[105];

int main()
{
    int T, M;
    int F[1005];
    cin >> T >> M;
    for (int i = 1; i <= M; i++)
    {
        cin >> nodes[i].t >> nodes[i].w;
    }
    for (int i = 1; i <= M; i++)
    {
        for (int t = T; t = 0; t--)
        {
            F[T] = max(F[t], F[T - nodes[i].t] + nodes[i].w);
        }
    }

    return 0;
}