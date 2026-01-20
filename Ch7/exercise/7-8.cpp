// WA
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int maxd;

string x, y, z;
int x_len, y_len, z_len;
string s; // 举例： 7**8*
string change = "*0123456789";
int a, b, c;

/**
返回在固定的 s 下解的个数
pos - 如 pos 位置是通配符 *, replace 为 0-9
的数字
 */
int validate(int pos) {
  if (pos == (x_len + y_len)) {
    // 固定 a, b 的情况下，枚举可能的 c
    a = stoi(s.substr(0, x_len));
    b = stoi(s.substr(x_len, y_len));
    string ab = to_string(a * b);
    if (z_len != ab.length()) {
      return 0;
    }

    for (int i = 0; i < z_len; i++) { // 逐位检查
      if (s[x_len + y_len + i] == '*') {
        continue;
      }
      if (s[x_len + y_len + i] != ab[i]) {
        return 0;
      }
    }
    return 1; // 存在 1 种 c 的补全方式
  }
  if (s[pos] == '*') {
    int solution_count = 0;
    for (int i = 0; i <= 9; i++) {
      if (i == 0 && (pos == 0 || pos == x_len)) {
        continue;
      }
      s[pos] = '0' + i;
      solution_count += validate(pos + 1);
      s[pos] = '*';
      if (solution_count > 1) {
        break;
      }
    }
    return solution_count;
  } else {
    return validate(pos + 1);
  }
}

void printAns() {
  for (int i = 0; i < x_len; i++) {
    printf("%c", s[i]);
  }
  printf(" ");
  for (int i = x_len; i < (x_len + y_len); i++) {
    printf("%c", s[i]);
  }
  printf(" ");
  for (int i = (x_len + y_len); i < (x_len + y_len + z_len); i++) {
    printf("%c", s[i]);
  }
}
/*
pos - 当前要修改的位置，直接修改在全局变量 s
depth - 当前深度
*/
bool dfs(int pos, int depth) {

  if (depth == maxd) {
    if (validate(0) == 1) {
      printAns();
      return true;
    }
    return false;
  }
  if (pos == s.length()) {
    return false;
  }

  // pos 位置尝试修改
  bool openingZero = pos == 0 || pos == x_len ||
                     pos == (x_len + y_len); // 这个位置不能替换成零
  for (int i = 0; i <= 10; i++) {
    char candidate = change[i];
    if (candidate == '0' && openingZero) {
      continue;
    }
    int offset = s[pos] == candidate ? 0 // 也可以选择不修改，直接看下一个位置
                                     : 1;
    char tmp = s[pos];
    s[pos] = candidate; // 直接改在 s
    if (dfs(pos + 1, depth + offset)) {
      return true;
    }
    s[pos] = tmp; // 回溯
  }
  return false;
}

int main() {
  int kase = 0;

  while (cin >> x) {
    if (x == "0")
      break;
    cin >> y >> z;
    x_len = x.length();
    y_len = y.length();
    z_len = z.length();
    s = x + y + z;

    cout << "Case " << ++kase << ": ";

    for (maxd = 0;; maxd++) {
      if (dfs(0, 0)) {
        break;
      }
    }
    cout << '\n';
  }
  return 0;
}