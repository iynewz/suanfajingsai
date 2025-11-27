#include <iostream>
// 264137058
// 815736402
using namespace std;
typedef int State[9];
const int maxstate = 1000000;
State st[maxstate], goal;
int dist[maxstate];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int bfs()
{
    int front = 1;
    int rear = 2;
    while (front < rear)
    {
        State &s = st[front]; // 当前正在处理的状态
        if (memcmp(s, goal, sizeof(s)) == 0)
        {
            return front; // st[front] 就是目标状态
        }
        int z;
        for(z = 0; z < 9; z++) {
            if(s[z] == 0) {
                break;
            }
        }
        //0,1,2
        //3,4,5
        //6,7,8
        int x = z/3;
        int y = z%3;
        for(int d = 0; d<4; d++) {
            int newx = x + dx[d];
            int newy = y + dy[d];
            int newz = newx * 3 + newy;
        }
        if(newx >= 0 && newx)
    }
}

int main()
{
    for (int i = 0; i < 9; i++)
    {
        cin >> State[1][i];
    }
    for (int i = 0; i < 9; i++)
    {
        cin >> goal[i];
    }
    int ans = bfs();
    return 0;
}