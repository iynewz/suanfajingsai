// P9946 [USACO20JAN] Word Processor B
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
    string word;
    int current_count = 0; // 当前行字符数

    for (int i = 0; i < N; i++)
    {
        cin >> word;
        int word_len = word.size();
        int new_len = current_count + word_len;
        if (new_len <= K)
        {
            current_count == 0 ? cout << word
                               : cout << ' ' << word;
            current_count = new_len;
        }
        else
        {
            cout << endl
                 << word;
            current_count = word_len;
        }
    }
    cout << endl;
    return 0;
}