// Ananagrams, UVa156
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<string, int> dict_map; // 字典映射，key 是单词的字母排序后的字符串，value 是出现次数
vector<string> dict;       // raw dictionary

string progress_word(string &word)
{
    string ans = word;
    for (int i = 0; i < word.size(); i++)
    {
        ans[i] = tolower(word[i]);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main()
{
    string word;
    while (cin >> word)
    {
        if (word == "#")
        {
            break; // 结束输入
        }
        dict.push_back(word);

        word = progress_word(word);

        if (dict_map.count(word) == 0)
        {
            dict_map[word] = 1; // 如果字典中没有这个单词，添加它
        }
        else
        {
            dict_map[word]++; // 如果已经有了
        }
    }
    set<string> answer;
    for (int i = 0; i < dict.size(); i++)
    {
        if (dict_map[progress_word(dict[i])] == 1)
        {
            answer.insert(dict[i]); // 如果单词的计数为1，添加到答案集合
        }
    }
    for (set<string>::iterator it = answer.begin(); it != answer.end(); ++it)
    {
        cout << *it << "\n";
    }
    return 0;
}