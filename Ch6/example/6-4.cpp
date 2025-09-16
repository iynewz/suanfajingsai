#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 100000 + 5;
char s[maxn];
int last, cursor;
int next_ptr[maxn];

int main()
{
    while (scanf("%s", s + 1) == 1)
    {
        int len = strlen(s + 1);
        last = cursor = 0;
        next_ptr[0] = 0;

        for (int i = 1; i <= len; i++)
        {
            char ch = s[i];
            // cout << ch;
            if (ch == '[')
            {
                cursor = 0;
            }
            else if (ch == ']')
            {
                cursor = last;
            }
            else
            {
                next_ptr[i] = next_ptr[cursor];
                next_ptr[cursor] = i;
                if (cursor == last)
                {
                    last = i;
                }
                cursor = i;
            }
        }
        for (int i = next_ptr[0]; i; i = next_ptr[i])
        {
            printf("%c", s[i]);
        }
        printf("\n");
    }
    return 0;
}