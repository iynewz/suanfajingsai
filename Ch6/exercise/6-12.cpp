//wrong ans but i don't see why
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

const int maxR = 10 + 5, maxC = 10 + 5;
const int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
const int dc[] = {0, 0, -1, 1};

int leftTable[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    // top = 1
    //     2  3  4  5
    {0, 0, 4, 2, 5, 3, 0},
    // top = 2
    //  1  2  3  4  5  6
    {0, 3, 0, 6, 1, 0, 4},
    // top = 3
    //  1  2  3  4  5  6
    {0, 5, 1, 0, 0, 6, 2},
    // top = 4
    //  1  2  3  4  5  6
    {0, 2, 6, 0, 0, 1, 5},
    // top = 5
    //  1  2  3  4  5  6
    {0, 4, 0, 1, 6, 0, 3},
    // top = 6
    //  1  2  3  4  5  6
    {0, 0, 3, 5, 2, 4, 0}};

struct State
{
    int r, c;
    int top, front;
    State(int r = 0, int c = 0, int top = 0, int front = 0) : r(r), c(c), top(top), front(front) {}
};

int d[maxR][maxC][7][7];
int maze[maxR][maxC];
int R, C;

struct Move
{
    int top, front; // new position
};

Move rollDice(int top, int front, int dir)
{
    Move m;
    int bottom = 7 - top;
    int back = 7 - front;
    int left = leftTable[top][front];
    int right = 7 - left;

    switch (dir)
    {
    case 0: // UP
        m.top = front;
        m.front = bottom;
        break;
    case 1: // DOWN
        m.top = back;
        m.front = top;
        break;
    case 2: // LEFT
        m.top = right;
        m.front = front;
        break;
    case 3: // RIGHT
        m.top = left;
        m.front = front;
        break;
    }
    return m;
}

void solve(int startR, int startC, int startTop, int startFront)
{
    queue<State> q;
    memset(d, -1, sizeof(d));
    State start(startR, startC, startTop, startFront);
    d[startR][startC][startTop][startFront] = 0;
    q.push(start);
    while (!q.empty())
    {
        State cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (nr < 1 || nr > R || nc < 1 || nc > C)
            {
                continue;
            }
            if (maze[nr][nc] == 0) // 不能走
            {
                continue;
            }
          
            Move next = rollDice(cur.top, cur.front, i);
            if (maze[nr][nc] != -1 && maze[nr][nc] != next.top)
            {
                continue;
            }
            if (d[nr][nc][next.top][next.front] != -1)
            {
                continue;
            }
            if (nr == startR && nc == startC)
            {
                cout << d[cur.r][cur.c][cur.top][cur.front] + 1 << " moves" << endl;
                return;
            }
            d[nr][nc][next.top][next.front] = d[cur.r][cur.c][cur.top][cur.front] + 1;
            q.push(State(nr, nc, next.top, next.front));
        
        }
    }
    cout << "No solution" << endl; // ✅ 如果 BFS 没有找到路径
}

int main()
{
    int startr, startc, top, front;
    string name;
    while (cin >> name && name != "END")
    {
        cout << name << endl;
        cin >> R >> C >> startr >> startc >> top >> front;
        for (int i = 1; i <= R; i++)
        {
            for (int j = 1; j <= C; j++)
            {
                cin >> maze[i][j];
            }
        }
        solve(startr, startc, top, front);
        // print solution
    }
    return 0;
}