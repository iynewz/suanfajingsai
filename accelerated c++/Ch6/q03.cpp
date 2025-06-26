#include <iostream>
#include <vector>
#include <algorithm>

using std::copy;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> u(10, 100);
    vector<int> v; // v is an empty vector, size 0

    // the code throws an error if we use v.begin()
    copy(u.begin(), u.end(), v.begin()); // THIS IS THE PROBLEM LINE

    return 0;
}