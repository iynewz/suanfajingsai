#include <string>
#include <iostream>

using namespace std;

int d[3] = {-1, 1, 0};

bool f[105][105]; // f[i][j]表示(i,j)上是否含有地雷。bool定义为全局变量时默认初始化为false
int ans[105][105];
int sta(int x, int y)
{
    /*给定坐标(x,y), 统计其周边有多少个雷*/
    int res = 0;
    for (int i = 0; i < 3; i++)
    {
        // 周边点的元素, 用数组(存坐标偏移)+循环, 减少代码量
        for (int j = 0; j < 3; j++)
        {
            if (f[x + d[i]][y + d[j]])
            {
                res++;
                return res;
            }
        }
    }
    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;
    string s;
    for (int i = 1; i <= n; i++) // 从下标1开始存地雷图, 就不需要考虑边界的问题
    {
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            if (s[j - 1] == '*') // string的下标从0开始
            {
                f[i][j] = true; // 说明这一个格子有地雷
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (f[i][j])
            {
                cout << "*";
            }
            else
            {
                cout << sta(i, j);
            }
        }
        cout << endl;
    }
}