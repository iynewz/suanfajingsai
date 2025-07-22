#include <iostream>
using namespace std;
int main()
{
    char WL[25 * 2500], c;
    int group_rule[2] = {11, 21};
    int L = 0;
    while (1)
    {
        cin >> c;
        if (c == 'E')
        {
            break;
        }
        else
        {
            WL[L++] = c;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        int group = group_rule[i];
        int w = 0, l = 0;
        for (int j = 0; j < L; j++)
        {
            if (WL[j] == 'W')
            {
                w++;
            }
            else if (WL[j] == 'L')
            {
                l++;
            }
            if ((w >= group || l >= group) && abs(w - l) >= 2)
            {
                cout << w << ":" << l << endl;
                w = 0;
                l = 0;
            }
        }

        cout << w << ":" << l << "\n"
             << endl;
        w = 0;
        l = 0;
    }
    return 0;
}