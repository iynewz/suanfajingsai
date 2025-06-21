#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    const int N = 100;
    for (int i = 0; i < N; i++)
    {
        int square = i * i;
        cout << setw(3) << i << setw(6) << i * i << endl;
    }
    return 0;
}