#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Node
{
    int x, y;
    Node(int x = 0, int y = 0) : x(x), y(y) {}
};

int direction[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

bool inside_board(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
};

int bfs(const Node &start, const Node &end)
{
    if (start.x == end.x && start.y == end.y)
    {
        return 0;
    }
    int dist[8][8];
    memset(dist, -1, sizeof(dist));
    queue<Node> q;
    q.push(start);
    dist[start.x][start.y] = 0;
    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int new_x = cur.x + direction[i][0];
            int new_y = cur.y + direction[i][1];
            if (inside_board(new_x, new_y) && dist[new_x][new_y] == -1)
            {
                dist[new_x][new_y] = dist[cur.x][cur.y] + 1;
                if (new_x == end.x && new_y == end.y)
                {
                    return dist[new_x][new_y];
                }
                else
                {
                    q.push(Node(new_x, new_y));
                }
            }
        }
    }
    return -1;
}

int main()
{
    char temp_u[3];
    char temp_v[3];
    while (cin >> temp_u >> temp_v)
    {
        Node start(temp_u[0] - 'a', temp_u[1] - '1');
        Node end(temp_v[0] - 'a', temp_v[1] - '1');
        int steps = bfs(start, end);
        cout
            << "To get from " << temp_u << " to " << temp_v << " takes " << steps << " knight moves." << endl;
    }
    return 0;
}