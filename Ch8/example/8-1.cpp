// Stacks of Flapjacks, UVa120
// https://xuanwo.io/2014/11/04/UVa-120-Stacks-of-Flapjacks/
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
const int maxn = 35;
int a[maxn];
int b[maxn];

bool check(int a) { return false; };
int main() {
  string s;
  while (getline(cin, s)) {
    // cout << s << endl;
    istringstream iss(s);
    deque<int> deq;
    int tmp;
    while (iss >> tmp) {
      deq.push_front((tmp));
    }
    for (deque<int>::iterator it = deq.begin(); it != deq.end(); it++) {
      deque<int>::iterator Max = max_element(it, deq.end());
      if (Max != it) {
        if (Max != deq.end() - 1) {
          reverse(Max, deq.end());
          cout << distance(deq.begin(), Max) + 1 << ' ';
        }
        reverse(it, deq.end());
        cout << distance(deq.begin(), it) + 1 << ' ';
      }
    }
    cout << "0\n";
  }
  return 0;
}