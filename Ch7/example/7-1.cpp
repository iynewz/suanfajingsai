#include <iostream>
// 79546 / 01283 = 62
using namespace std;

bool checkDigitUnique(const int x, const int y)
{
    int a = x, b = y;
    // cout << a << " " << b;
    int digits[10 + 5] = {0};
    int tmp = 5;
    while (tmp--)
    {
        digits[a % 10]++;
        digits[b % 10]++;
        a /= 10;
        b /= 10;
    }
    for (int i = 0; i <= 9; i++)
    {
        // cout << i << ": " << digits[i] << endl;
        if (digits[i] > 1)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int N;
    int isFirst = true;
    while (cin >> N && N)
    {
        if(!isFirst) {
            printf("\n");
        }
        isFirst = false;
        bool hasAns = false;
        for (int i = 1234; i <= 98765; i++)
        {
            int a = i * N;
            if (a > 98765)
            {
                continue;
            }
            bool isValid = checkDigitUnique(a, i);
            if (isValid)
            {
                hasAns = true;
                printf("%05d / %05d = %d\n", a, i, N);
            }
        }

        if(!hasAns) {
            printf("There are no solutions for %d.\n", N);
        }
    }
    return 0;
}
