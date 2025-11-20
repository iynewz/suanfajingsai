#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int k;
    while (scanf("%d", &k) == 1 && k)
    {
        vector<int> X, Y;
        int end = k * 2;
        for (int y = k + 1; y <= end; y++)
        {
            int num = k * y;
            int den = y - k;
            if (num % den == 0)
            {
                int x = num / den;
                X.push_back(x);
                Y.push_back(y);
            }
        }
        printf("%d\n", (int)X.size());
        for (int i = 0; i < X.size(); i++)
        {
            printf("1/%d = 1/%d + 1/%d\n", k, X[i], Y[i]);
        }
    }

    return 0;
}