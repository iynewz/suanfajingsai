#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;
    vector<string> words;
    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        words.push_back(s);
    }
    int current_count = 0; // 当前行字符数
    int p = 0;

    for (int i = 0; i < words.size(); i++)
    {
        int word_len = words[i].size();
        int new_len = current_count + word_len;
        if (current_count == 0)
        {
            cout << words[i];
            current_count += word_len;
        }
        else if (new_len <= K)
        {
            cout << ' ' << words[i];
            current_count = new_len;
        }
        else
        {
            cout << endl
                 << words[i];
            current_count = word_len;
        }
    }
    cout << endl;
    return 0;
}