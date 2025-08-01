#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    string s1, s2;
    int ans = 1;
    cin >> s1 >> s2;
    reverse(s1.begin(), s1.end());

    for (int i = 0; i < s1.size() - 1; i++)
    {
        if (int(s2.find(s1.substr(i, 2))) != -1)
        { // 如果可以找到 反序
            ans <<= 1;
        }
    }
    cout << ans << endl;
    return 0;
}