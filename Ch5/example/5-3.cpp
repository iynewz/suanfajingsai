// Andy's First Dictionary. UVa 10815
#include <iostream>
#include <string>
#include <set>
#include <sstream>
using namespace std;

int main()
{
    set<string> dict;
    string s, buffer;
    while (cin >> s)
    {
        // 处理小写，过滤我们不需要的字符
        for (int i = 0; i < s.size(); i++)
        {
            if (isalpha(s[i]))
            {
                s[i] = tolower(s[i]);
            }
            else
            {
                s[i] = ' ';
            }
        }
        stringstream ss(s);
        while (ss >> buffer) // 使用 stringstream 处理空格分隔的单词
        {
            dict.insert(buffer); // 将处理后的单词插入字典
        }
    }
    for (set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
    {
        cout << *it << endl; // 输出字典中的单词
    }
    return 0;
}