// lrj P125
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

struct BigInteger
{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;
    BigInteger(long long num = 0)
    {
        *this = num;
    }
    BigInteger operator=(long long num)
    {
        s.clear();
        do
        {
            s.push_back(num % BASE);
            num /= BASE;

        } while (num > 0);
        return *this;
    }
    BigInteger operator=(const string &str)
    {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++)
        {
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }
    BigInteger operator+(const BigInteger &b) const
    {
        BigInteger c;
        c.s.clear();
        for (int i = 0, g = 0;; i++)
        {
            if (g == 0 && i >= s.size() && i >= b.s.size())
            {
                break;
            }
            int x = g;
            if (i < s.size())
            {
                x += s[i];
            }
            if (i < b.s.size())
            {
                x += b.s[i];
            }
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
};

ostream &
operator<<(ostream &out, const BigInteger &x)
{
    out << x.s.back(); // 先输出最高位（无前导零）
    for (int i = (int)x.s.size() - 2; i >= 0; i--)
    {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]); // 中间部分补零到8位
        for (int j = 0; j < strlen(buf); j++)
        {
            out << buf[j];
        }
    }
    return out;
}

istream &operator>>(istream &in, BigInteger &x)
{
    string s;
    if (!(in >> s))
    {
        return in;
    }
    x = s;
    return in;
}

int main()
{
    BigInteger a;
    cout << "请输入一个大整数: ";
    cin >> a;
    cout << "你输入的是: " << a << endl;
    return 0;
}
