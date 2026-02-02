#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
const int maxn = 20;

char operators[] = "*+-";
int maxd;
vector<string> ans; // all possible ans

// 试着在每个位置放符号

/**
在 s 的第 idx 个位置尝试插入运算符或者跳过
在每个位置插入 + - * 或不插，生成所有可能表达式
*/
void dfs(int idx, string s) {
  if (idx == s.size()) {

    ans.push_back(s);
    return;
  } else {
    for (int i = 0; i < 3; i++) {
      string tmp = s;
      tmp.insert(idx, 1, operators[i]);
      dfs(idx + 2, tmp);
    }
    dfs(idx + 1, s);
  }
}
void test_print_possible() {
  for (auto i : ans) {
    cout << i << endl;
  }
}

// 21-0+01+0+0  // true
// 21-0+101+0+0 // false
// 数字开头是 '0' 且数字长度 > 1
bool hasLeadingZero(const string &s) {
  //   cout << s << " ";

  int len = s.length();
  for (int i = 0; i < len;) {
    if (isdigit(s[i])) {
      int start = i;
      while (i < len && isdigit(s[i])) {
        i++;
      }
      if (i - start > 1 && s[start] == '0') {
        // printf("yes\n");
        return true;
      }
    } else {
      i++;
    }
  }
  //   printf("no leading zero\n");
  return false;
}

bool allDigits(const string &s) {
  for (char ch : s) {
    if (!isdigit(ch)) {
      return false;
    }
  }
  return true;
}

int calculate(const string &s) {
  stack<int> num;
  char op = '+';
  int len = s.length();

  for (int i = 0; i < len;) {
    if (isdigit(s[i])) {
      int tmp_num = 0;
      while (isdigit(s[i])) {
        tmp_num = 10 * tmp_num + (s[i] - '0');
        i++;
      }
      //   cout << " tmp_num: " << tmp_num << " ";
      // 根据上一个运算符，决定怎么处理这个数
      if (op == '*') {
        int op1 = num.top();
        num.pop();
        num.push(op1 * tmp_num);
      } else if (op == '+') {
        num.push(tmp_num);
      } else if (op == '-') {
        num.push(0 - tmp_num);
      }
    } else {
      // s[i] 是 * + -
      op = s[i];
      i++;
    }
  }
  int result = 0;
  while (!num.empty()) {
    result += num.top();
    num.pop();
  }
  return result;
}

bool validate(const string &s) {
  if (hasLeadingZero(s)) {
    return false;
  }
  if (allDigits(s)) {
    return false;
  }
  if (calculate(s) == 2000) {
    return true;
  }
  return false;
}

int main() {
  int T = 1;
  string s;

  while (cin >> s && s[0] != '=') {
    ans.clear();
    printf("Problem %d\n", T++);
    s.pop_back();
    // cout << s << endl;
    dfs(1, s);
    // test_print_possible();
    bool hasAns = false;
    for (auto i : ans) {
      if (validate(i)) {
        cout << "  " << i << "=" << endl;
        hasAns = true;
      };
    }
    if (!hasAns) {
      printf("  IMPOSSIBLE\n");
    }
  }

  return 0;
}