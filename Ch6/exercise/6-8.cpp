#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
const int maxn = 64 + 5;
int buf[maxn][maxn];

vector<int> paths;

void grid_to_path(int x, int y, int width, int weight, int depth)
{
    bool has_black = false;
    bool has_white = false;

    for (int i = x; i < x + width; i++)
    {
        for (int j = y; j < y + width; j++)
        {
            if (buf[i][j] == 1)
            {
                has_black = true;
            }
            else
            {
                has_white = true;
            }
        }
    }

    if (has_white && !has_black) // all white
    {
        return;
    }
    else if (has_black && !has_white) // all black, accumulate to paths
    {
        paths.push_back(weight);
        return;
    }
    else if (has_black && has_white) // mixed color, continue dfs
    {
        int half = width / 2;
        int base = 1;
        for (int d = 0; d < depth; d++)
        {
            base *= 5;
        }
        grid_to_path(x, y, half, weight + base * 1, depth + 1);
        grid_to_path(x, y + half, half, weight + base * 2, depth + 1);
        grid_to_path(x + half, y, half, weight + base * 3, depth + 1);
        grid_to_path(x + half, y + half, half, weight + base * 4, depth + 1);
    }
}

void path_to_grid(int width)
{
    memset(buf, 0, sizeof(buf));
    for (int p : paths)
    {
        if (p == 0)
        {
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    buf[i][j] = 1;
                }
            }
            continue;
        }
        int temp = p;

        vector<int> directions; // 只可能是 0, 1, 2, 3, 4
        while (temp > 0)
        {
            directions.push_back(temp % 5);
            temp /= 5;
        }

        int x = 0, y = 0, size = width;
        for (int dir : directions)
        {
            size /= 2;
            switch (dir)
            {
            case 1:
                break; // NW
            case 2:
                y += size;
                break; // NE
            case 3:
                x += size;
                break; // SW
            case 4:
                x += size;
                y += size;
                break; // SE
            }
        }
        for (int i = x; i < x + size; i++)
        {
            for (int j = y; j < y + size; j++)
            {
                buf[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << (buf[i][j] ? '*' : '.');
        }
        cout << endl;
    }
}

int main()
{

    int case_num = 1;
    while (cin >> n && n)
    {
        if (case_num > 1)
        {
            cout << "\n";
        }
        cout << "Image " << case_num++ << endl;
        memset(buf, 0, sizeof(buf));
        paths.clear();
        if (n > 0)
        {
            string tmp;
            for (int i = 0; i < n; i++)
            {
                cin >> tmp;
                for (int j = 0; j < n; j++)
                {
                    buf[i][j] = tmp[j] - '0';
                }
            }

            grid_to_path(0, 0, n, 0, 0);
            sort(paths.begin(), paths.end());

            for (int i = 0; i < paths.size(); i++)
            {
                if (i > 0)
                {
                    if (i % 12 == 0)
                    {
                        cout << endl;
                    }
                    else
                    {
                        cout << " ";
                    }
                }
                cout << paths[i];
            }
            if (paths.size() > 0)
            {
                cout << "\n";
            }
            cout << "Total number of black nodes = " << paths.size() << endl;
        }
        else
        {
            int tmp;
            while (cin >> tmp && tmp != -1)
            {
                paths.push_back(tmp);
            }
            path_to_grid(-n);
        }
    }
    return 0;
}