// https : // prprprpony.github.io/blog/2016/07/04/uva-12113/
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> ok;
vector<vector<bool>> vis;

int pos(int r, int c) { return r * 9 + c; }

void putSquare(string &s, int r, int c) {
  c = c * 2; // r: 0, 1, 2; c: 0, 2, 4
  // 构造以 (r, c) 作为左上角的正方图案
  //    _ _   #
  //   |   |  #
  //   |_ _|  #
  //          #
  s[pos(r, c + 1)] = s[pos(r, c + 3)] = '_';
  s[pos(r + 2, c + 1)] = s[pos(r + 2, c + 3)] = '_';
  s[pos(r + 1, c)] = s[pos(r + 1, c + 4)] = '|';
  s[pos(r + 2, c)] = s[pos(r + 2, c + 4)] = '|';
  s[pos(r + 1, c + 1)] = s[pos(r + 1, c + 2)] = ' ';
  s[pos(r + 1, c + 3)] = s[pos(r + 2, c + 2)] = ' ';
}
void printsqr(const string &s) {
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 9; ++c)
      cout << s[pos(r, c)];
    cout << "#\n";
  }
  cout << '\n';
}
void build(string &s, int draw, int target) {
  if (draw > target) {
    return;
  }
  if (ok.count(s)) {
    return;
  }
  if (draw > 0) {
    ok.insert(s);
  }
  //   printsqr(s);
  string tmp = s;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!vis[i][j]) {
        vis[i][j] = true;
        putSquare(s, i, j);
        build(s, draw + 1, target); // s 会被改
        s = tmp;
        vis[i][j] = false;
      }
    }
  }
}

int main() {
  vis.assign(3, vector<bool>(3, false));
  string s(45, ' ');
  // 所有画法存入 set
  build(s, 0, 6);

  int kase = 0;

  while (getline(cin, s) && s[0] != '0') {
    s.pop_back(); // 去掉行尾的 #
    for (int i = 0; i < 4; ++i) {
      string t;
      getline(cin, t);
      t.pop_back();
      s += t;
    }
    cout << "Case " << ++kase << ": " << (ok.count(s) ? "Yes" : "No") << '\n';
  }
  return 0;
}