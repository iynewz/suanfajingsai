#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
int main()
{
    int N;
    char c[65];
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> c;
        int len = strlen(c);
        int last_number = c[len - 1] - '0';
        if (last_number % 2 == 0)
        {
            cout << "even" << endl;
        }
        else
        {
            cout << "odd" << endl;
        }
    }
    return 0;
}