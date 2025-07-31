// ❌ TLE: 只用了高精度，查询没有优化。很慢。
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct BigInteger
{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger(long long num = 0) { *this = num; }

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
                break;
            int x = g;
            if (i < s.size())
                x += s[i];
            if (i < b.s.size())
                x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }

    string toString() const
    {
        stringstream ss;
        ss << s.back();
        for (int i = (int)s.size() - 2; i >= 0; i--)
        {
            char buf[20];
            sprintf(buf, "%08d", s[i]);
            ss << buf;
        }
        return ss.str();
    }
};

string get_prefix(const BigInteger &num, int k)
{
    string s = num.toString();
    return s.substr(0, min(k, (int)s.length()));
}

int find_min_n(const string &target, int k)
{
    BigInteger a = 1, b = 1;

    for (int n = 0; n < 100000; n++)
    {
        string prefix = get_prefix(a, k);
        if (prefix == target)
        {
            return n;
        }

        BigInteger next = a + b;
        a = b;
        b = next;
    }
    return -1;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        string prefix;
        cin >> prefix;
        int n = find_min_n(prefix, prefix.length());
        cout << "Case #" << i << ": " << n << endl;
    }
    return 0;
}