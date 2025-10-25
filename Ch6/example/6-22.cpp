#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1000 + 10;

class Node
{
public:
    float x, y, r;
    Node(double x, double y, double r) : x(x), y(y), r(r) {}
};

vector<Node> nodes;
vector<vector<int>> adj; // 邻接表
bool visited[maxn];

bool is_intersect(const Node &a, const Node &b)
{
    double dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return dist <= (a.r + b.r) * (a.r + b.r);
}
vector<double> left, right;
void check_left_right(int u)
{
    if (nodes[u].x <= nodes[u].r)
    { // touch left border
        double y = nodes[u].y - sqrt(nodes[u].r * nodes[u].r - nodes[u].x * nodes[u].x);
        left.push_back(y);
    }
    if (nodes[u].x + nodes[u].r >= 1000)
    {
        double y = nodes[u].y - sqrt(nodes[u].r * nodes[u].r - (1000 - nodes[u].x) * (1000 - nodes[u].x));
        right.push_back(y);
    }
}

void dfs(int u)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (visited[v] == false)
        {
            dfs(v);
        }
    }
    check_left_right(u);
}

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        nodes.clear();
        adj.clear();
        adj.assign(n, vector<int>()); // 必须
        memset(visited, false, sizeof(visited));
        left.clear();
        right.clear();

        for (int i = 0; i < n; i++)
        {
            double x, y, r;
            scanf("%lf %lf %lf", &x, &y, &r);
            nodes.push_back({x, y, r});
        }
        // build graph
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                bool has_edge = is_intersect(nodes[i], nodes[j]);
                if (has_edge)
                {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        // find if touch top and bottom
        vector<int> top, bottom;

        for (int i = 0; i < n; i++)
        {
            if (nodes[i].y + nodes[i].r >= 1000)
            {
                top.push_back(i);
            }
            if (nodes[i].y - nodes[i].r <= 0)
            {
                bottom.push_back(i);
            }
        }
        int is_blocked = false;
        for (int i : top)
        {
            if (visited[i] == false)
            {
                dfs(i);
            }
        }
        for (int i : bottom)
        {
            if (visited[i] == true)
            {
                is_blocked = true;
                break;
            }
        }
        if (is_blocked)
        {
            printf("IMPOSSIBLE\n");
        }
        else
        {
            double in, out;
            if (left.size() != 0)
            {
                auto min_left = min_element(left.begin(), left.end());
                in = *min_left;
            }
            else
            {
                in = 1000.0;
            }
            if (right.size() != 0)
            {
                auto min_right = min_element(right.begin(), right.end());
                out = *min_right;
            }
            else
            {
                out = 1000.0;
            }

            printf("0.00 %.2lf 1000.00 %.2lf\n", in, out);
        }
    }
    return 0;
}