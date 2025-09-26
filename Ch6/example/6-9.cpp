#include <iostream>
#include <queue>

using namespace std;
int T;

bool solve(int &weight)
{
    int w1, l1, w2, l2;
    cin >> w1 >> l1 >> w2 >> l2;
    bool b1 = true, b2 = true; // 子天平是否平衡
    if (w1 == 0)
    {
        b1 = solve(w1);
    }
    if (w2 == 0)
    {
        b2 = solve(w2);
    }
    weight = w1 + w2;
    return b1 && b2 && w1 * l1 == w2 * l2;
}
int main()
{
    int weight;
    cin >> T;
    while (T--)
    {
        if (solve(weight))
        {
            cout << "YES"
                 << endl;
        }
        else
        {
            cout << "NO"
                 << endl;
        }
        if (T)
        {
            cout << "\n";
        }
    }
    return 0;
}