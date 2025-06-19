#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxcol = 60;
const int maxn = 100 + 5;
string filenames[maxn];

void print(const string &s, int len, char extra)
{
    cout << s;
    cout << string(len - s.length(), extra);
}

int main()
{
    int n;
    while (cin >> n)
    {
        int M = 0; // 最长的单词的长度

        for (int i = 0; i < n; i++)
        {
            cin >> filenames[i];
            int curr_len = filenames[i].length();
            M = max(M, curr_len);
        }
        // cout << M << endl;
        // calculate columns
        // M+2; M+2; ... M
        int columns = (maxcol - M) / (M + 2) + 1;
        int rows = (n - 1) / columns + 1;
        cout << string(maxcol, '-') << endl;
        sort(filenames, filenames + n);
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                int idx = c * rows + r;
                if (idx < n)
                {
                    print(filenames[idx], c == (columns - 1) ? M : M + 2, ' ');
                }
            }
            cout << endl;
        }
    }

    return 0;
}