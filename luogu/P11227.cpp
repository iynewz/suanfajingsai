#include <iostream>
#include <set>
#include <string>
using namespace std;
// DCHS
// A23456789TJQK

set<string> cards;
int n;
int main()
{
    cin >> n;
    while (n--)
    {
        string str;
        cin >> str;
        cards.insert(str);
    }
    cout << 52 - cards.size() << endl;
    return 0;
}