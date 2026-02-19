#include <iostream>
using namespace std;
int main() {
  int n;
  while (cin >> n) {
    cout << "2 " << n << " " << n << endl;
    // layer 1
    for (int i = 0; i < n; i++) {
      char tmp = char('a' + i);
      if (i >= 26) {
        tmp = char('A' + i - 26);
      }
      for (int j = 0; j < n; j++) {
        cout << tmp;
      }
      cout << "\n";
    }
    cout << "\n";
    // layer 2
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char tmp = char('a' + j);
        if (j >= 26) {
          tmp = char('A' + j - 26);
        }
        cout << tmp;
      }
      cout << '\n';
    }
  }
  return 0;
}