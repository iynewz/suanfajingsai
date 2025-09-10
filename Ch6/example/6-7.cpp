#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    string s = "(11,LL)";
    int v;
    sscanf(&s[1], "%d", &v);
    cout << v << endl;
    return 0;
}