#include <iostream>
#include <algorithm>

#define maxn 20005
using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    int n, B;
    cin >> n >> B;
    int a[maxn];
    for (int i = 0; i < n; i++)
    {
        int h;
        cin >> h;
        a[i] = h;
    }
    sort(a, a + n, cmp);

    int count = 0;
    int sum = a[0];
    while (sum < B)
    {
        count++;
        sum += a[count];
    }
    cout << ++count << endl;

    return 0;
}