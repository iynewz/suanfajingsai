#include <iostream>
using namespace std;

int n, w;
const int MAX_SCORE = 600;
int score[MAX_SCORE + 5] = {0};
int first_flag = 0;

int main()
{
    cin >> n >> w;
    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        score[tmp]++; // 存
        // 计算 win
        int win_count = max(1, (i * w) / 100);
        // cout << "i:" << i << " " << win_count << endl;
        int adder = 0;
        for (int j = 600; j >= 0; j--)
        {
            adder += score[j];
            if (adder >= win_count)
            {
                if (first_flag)
                {
                    cout << " ";
                }
                cout << j;
                first_flag = 1;
                break;
            }
        }
    }
    cout << endl;
    return 0;
}