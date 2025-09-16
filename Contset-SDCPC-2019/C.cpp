// wrong answer
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int T;
int n, k;
int point[100000 + 5][2];

int main()
{
    cin >> T;
    while (T--)
    {
        int max_possible = 0;
        long long x = 0;
        long long y = 0;
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
        {
            char c;
            cin >> c;
            if (c == 'R')
            {
                x++;
            }
            else if (c == 'L')
            {
                x--;
            }
            else if (c == 'U')
            {
                y++;
            }
            else if (c == 'D')
            {
                y--;
            }
            point[i][0] = x;
            point[i][1] = y;
            int curr_dis = abs(x) + abs(y);
            if (curr_dis > max_possible)
            {
                max_possible = curr_dis;
            }
        }

        if (k == 1)
        {
            cout << max_possible << endl;
            continue;
        }
        for (int i = 1; i <= n; i++)
        {
            // 经过 k 轮
            int final_x = point[i][0] + (k - 1) * x;
            int final_y = point[i][1] + (k - 1) * y;
            max_possible = max(max_possible, (abs(final_x) + abs(final_y)));
        }
    }
    return 0;
}