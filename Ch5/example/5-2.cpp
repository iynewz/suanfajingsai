// The Blocks Problem, UVa101
#include <iostream>
#include <cstdio>
#include <vector>
#define maxn 30

using namespace std;
// move a onto b: 先把 a, b 以上的木块放回原位，再把 a 自身挪到 b 上方
// move a over b : 先把 a 以上的放回原位；再把 a 挪到包含 b 的列的最上方
// pile a onto b : b 上方的先放回原位；a 和 a 以上所有木块直接挪到 b 上方
// pile a over b : a 和 a 上方的直接挪到包含 b 的列的最上方

vector<int> pile[maxn];

void clear_above(int position, int height)
{
    // 把 position 上方高度为 height 的木块放回原位
    for (int i = height + 1; i < pile[position].size(); i++)
    {
        int block_value = pile[position][i];
        pile[block_value].push_back(block_value);
    }
    pile[position].resize(height + 1); // 清除 position 上方的木块
}

void find_position(int a, int &position, int &height) // 找到 a 在哪一列， 把 a 所在的列数赋值给 pa, 把 a 高度赋值给 ha
{
    for (position = 0; position < maxn; position++)
    {
        int column_size = pile[position].size();
        for (int i = 0; i < column_size; i++)
        {
            if (pile[position][i] == a)
            {
                height = i; // 找到 a 的高度
                return;     // 找到 a 所在的列
            }
        }
    }
}

void pile_onto(int pa, int ha, int pb)
{
    for (int i = ha; i < pile[pa].size(); i++)
    {
        int block_value = pile[pa][i];
        pile[pb].push_back(block_value); // 把 pa 上方的木块放到 pb 上
    }
    pile[pa].resize(ha); // 记得清除 pa 上方的木块
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        pile[i].push_back(i);
    }
    int a, b;
    string s1, s2;
    while (cin >> s1 >> a >> s2 >> b)
    {
        int pa, pb, ha, hb;
        find_position(a, pa, ha);
        find_position(b, pb, hb);
        if (a == b || pa == pb)
        {
            continue;
        }
        if (s1 == "move")
        {
            clear_above(pa, ha);
        }
        if (s2 == "onto")
        {
            clear_above(pb, hb);
        }
        pile_onto(pa, ha, pb);
    }
    for (int i = 0; i < n; i++)
    {
        cout << i << ":";
        for (int j = 0; j < pile[i].size(); j++)
        {
            cout << " " << pile[i][j];
        }
        cout << endl;
    }
    return 0;
}