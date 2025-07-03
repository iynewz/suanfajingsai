#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#define max_word 180 + 5
#define max_line 1000 + 5

using namespace std;

int main()
{
    vector<string> words;
    string sentence;
    vector<int> max_len;           // 记录每一列的 word 的最大长度
    vector<string> grid[max_line]; // 记录 word
    int line = 0;
    while (getline(cin, sentence))
    {
        string word;
        stringstream ss(sentence);
        int column = 0;
        while (ss >> word)
        {
            if (column >= max_len.size())
            {
                max_len.push_back(0);
            }
            int curr_word_len = word.size();
            if (curr_word_len > max_len[column])
            {
                max_len[column] = curr_word_len;
            }
            grid[line].push_back(word);
            column++;
        }
        line++;
    }

    for (int i = 0; i < line; i++)
    {
        // get line width:
        int len = grid[i].size();
        for (int j = 0; j < len; j++)
        {
            int space_count = max_len[j] - grid[i][j].size();
            if (j != len - 1)
            {
                cout << grid[i][j] << string(space_count, ' ');
                cout << " ";
            }
            else
            {
                cout << grid[i][j];
            }
        }
        cout << "\n";
    }

    return 0;
}
