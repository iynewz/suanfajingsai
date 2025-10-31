// https://blog.nowcoder.net/n/78ffbd5f23354eaa817cfb8672d52962
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

#define ll long long
string s;
int pos;
map<ll, int> cnt; // <力矩, 出现次数>
int leaves_total = 0;

void dfs(int depth)
{

    if (isdigit(s[pos]))
    {
        ll num = 0;
        while (isdigit(s[pos]))
        {
            num = num * 10 + (s[pos] - '0');
            pos++;
        }
        leaves_total++;
        ll weight = num * (1LL << depth);
        cnt[weight]++;
    }
    if (s[pos] == '[')
    {
        pos++;
        dfs(depth + 1); // 递归解析左边子天平
        pos++;          // skip ','
        dfs(depth + 1); // 递归解析右边子天平
        pos++;          // skip ')'
    }
    return;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> s;
        pos = 0; // 当前扫描到的字符位置
        cnt.clear();
        leaves_total = 0;
        dfs(0);
        int max_occur_count = 0;
        for (auto &p : cnt)
        {
            max_occur_count = max(max_occur_count, p.second);
        }

        cout << (leaves_total - max_occur_count) << "\n";
    }
    return 0;
}