#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
map<string, vector<pair<int, int>>> mp;
vector<string> document[100 + 5];

void print_doc_test()
{
    cout << "--This is a test for the code snippet.--" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "Document " << i << ":" << endl;
        for (const auto &line : document[i])
        {
            cout << line << endl;
        }
    }
}

void print_mp_test()
{
    /*
    word: {doc_id, line_id}, ... {doc_id, line_id}
    */
    cout << "--This is a test for the code snippet.--" << endl;
    for (const auto &pair : mp)
    {
        cout << pair.first << ": ";
        for (const auto &p : pair.second)
        {
            cout << "{" << p.first << ", " << p.second << "} ";
        }
        cout << endl;
    }
}

void record_words(string s, int doc_id, int line_id)
{
    string word;
    for (const auto &c : s)
    {
        if (isalpha(c))
        {
            word += tolower(c);
        }
        else
        {
            if (!word.empty())
            {
                mp[word].push_back({doc_id, line_id});
            }
            word.clear();
        }
    }
    if (!word.empty())
    {
        mp[word].push_back({doc_id, line_id});
    }
}

int main()
{
    int N, M;
    cin >> N;
    getchar();
    for (int i = 0; i < N; i++) // 第几篇文章
    {
        string s;
        int line = 0;
        while (getline(cin, s) && s[0] != '*')
        {
            document[i].push_back(s);
            record_words(s, i, line);
            line++;
        }
    }
    // print_doc_test();
    // print_mp_test();
    cin >> M;
    getchar();
    string query, t1, t2;
    while (M--)
    {
        getline(cin, query);
        set<pair<int, int>> output;
        int i = query.find(' '), j = query.rfind(' '); // 查找第一个和最后一个空格, 得出是 AND / OR / NOT / normal query
        if (i == string::npos)                         // normal query
        {
            output.insert(mp[query].begin(), mp[query].end());
        }
        else if (query.substr(0, i) == "NOT") // NOT
        {
            t1 = query.substr(i + 1);
            set<int> not_set;
            for (int i = 0; i < N; i++)
            {
                not_set.insert(i);
            }
            for (auto p : mp[t1])
            {
                not_set.erase(p.first);
            }
            // 单独输出
            for (auto p : not_set)
            {
                for (auto line : document[p])
                    cout << line << endl;
                if (p != *not_set.rbegin())
                    cout << "----------" << endl;
            }
            if (not_set.empty())
                cout << "Sorry, I found nothing.\n";
        }
        else // AND / OR
        {
            t1 = query.substr(0, i);
            t2 = query.substr(j + 1);
            if (query.substr(i + 1, j - i - 1) == "AND")
            {
                set<int> set1, set2;
                for (auto p : mp[t1])
                    set1.insert(p.first); // t1 所在 doc
                for (auto p : mp[t2])
                    if (set1.find(p.first) != set1.end())
                        set2.insert(p.first); // set2 是交集 doc
                for (auto p : mp[t1])
                {
                    if (set2.find(p.first) != set2.end())
                        output.insert(p); // 交集 doc 的行
                }
                for (auto p : mp[t2])
                {
                    if (set2.find(p.first) != set2.end())
                        output.insert(p); // 交集 doc 的行
                }
            }
            else // OR
            {
                output.insert(mp[t1].begin(), mp[t1].end());
                output.insert(mp[t2].begin(), mp[t2].end());
            }
        }
        // 输出
        int pre = -1; // 控制间隔输出
        if (query.substr(0, i) != "NOT")
        {
            for (auto p : output)
            {
                if (pre != -1 && pre != p.first)
                    cout << "----------" << endl; // 两个不同文章之间
                pre = p.first;
                cout << document[p.first][p.second] << endl;
            }
            if (output.empty())
                cout << "Sorry, I found nothing.\n";
        }
        cout << "==========" << endl;
    }
    return 0;
}