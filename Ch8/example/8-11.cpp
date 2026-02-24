#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int maxn = 5000 + 5;
int N;
int Huffman() {
  priority_queue<int, vector<int>, greater<int>> q;
  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;
    q.push(a);
  }
  int ans = 0;
  for (int i = 0; i < N - 1; i++) {
    int min1 = q.top();
    q.pop();
    int min2 = q.top();
    q.pop();
    q.push(min1 + min2);
    ans = ans + min1 + min2;
  }
  return ans;
}
int main() {
  while (cin >> N && N) {
    cout << Huffman() << endl;
  }
  return 0;
}