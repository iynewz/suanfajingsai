// hash
#include <string>
#include <iostream>

typedef unsigned long long ULL;

using namespace std;
// s1: abcxxxxabcxabcd
// s2: abcdxabcxxxxabcx

string s1, s2;
ULL preSum1[100], preSum2[100];
ULL px[100]; // px[i] 代表 p 的 i 次方
ULL subStrHash(int i, int L, int R)
{
    /* 求字符串 i 字串 [L,R] 的哈希值 */
    if (i == 1)
    {
        return preSum1[R] - preSum1[L - 1] * px[R - L + 1];
    }
    else
    {
        return preSum2[R] - preSum2[L - 1] * px[R - L + 1];
    }
}
int main()
{
    cin >> s1 >> s2;
    const ULL p = 131;

    for (int i = 1; i <= s1.size(); i++)
    {
        preSum1[i] = preSum1[i - 1] * p + s1[i - 1] * p;
    }
    for (int i = 1; i <= s2.size(); i++)
    {
        preSum2[i] = preSum2[i - 1] * p + s2[i - 1] * p;
    }

    px[0] = 1;

    int maxSize = max(s1.size(), s2.size());
    for (int i = 1; i <= maxSize; i++)
    {
        px[i] = px[i - 1] * p;
    }

    int minSize = min(s1.size(), s2.size());
    for (int i = minSize; i >= 1; i--)
    {
        if (subStrHash(1, 1, i) == subStrHash(2, s2.size() - i + 1, s2.size()) || subStrHash(1, s1.size() - i + 1, s1.size()) == subStrHash(2, 1, i))
        {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}