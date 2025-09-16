// https://www.luogu.com.cn/contest/276180#problems
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int T, y1, m1, d1;
int y2, m2, d2;
string s;
string day[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> y1 >> m1 >> d1 >> s;
        cin >> y2 >> m2 >> d2;

        long long y_offset = y2 - y1;
        long long m_offset = m2 - m1;
        long long d_offset = d2 - d1;

        long long total_offset = y_offset * 12 * 30 + m_offset * 30 + d_offset;

        int initial_index = 0;
        for (int i = 0; i < 5; i++)
        {
            if (day[i] == s)
            {
                initial_index = i;
                break;
            }
        }
        int day_offset = total_offset % 5;
        string result = day[(initial_index + day_offset + 5) % 5];
        cout << result << endl;
    }
    return 0;
}