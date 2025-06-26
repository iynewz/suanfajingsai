#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string s = "hsabc"; // 前2字符 "hs"
string test = "sh"; // 反向也是 "hs"
bool is_palindrome(const string &s)
{
    auto it1 = s.begin();
    auto it2 = test.rbegin();
    int count = 0;

    while (it1 != s.end())
    {
        cout << "比较 #" << ++count
             << ": " << *it1 << " vs " << *it2 << endl;

        if (*it1 != *it2)
            return false;

        ++it1;
        ++it2; // 当 it2 越界时可能崩溃！
    }
    return true;
}

int main()
{
    cout << boolalpha << is_palindrome(s) << endl; // 输出 true
    return 0;
}