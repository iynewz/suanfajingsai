#include <iostream>
using namespace std;

int n;
int C[100 + 5]; // C[x]表示第 x 行皇后的列编号
int tot = 0;    // 解的个数

void search(int r)
{
    if (r == n)
    {
        tot++;
    }
    for (int i = 0; i < n; i++)
    {
        int ok = 1;
        C[r] = i;
        for (int j = 0; j < r; j++)
        {
            if (C[r] == C[j] || r - C[r] == j - C[j] || r + C[r] == j + C[j])
            {
                ok = 0;
                break;
            }
        }
        if (ok)
        {
            search(r + 1);
        }
    }
}

int main()
{

    cin >> n;
    search(0);
    cout << tot << endl;
    return 0;
}