// learn from https://www.cnblogs.com/hkxy125/p/7982691.html
#include <cstdio>
#include <cstring>

using namespace std;
int n, K;
char ans[25][25];
char seat[25][25];

/*
id - 线性编号的格子位置 [0, n*n - 1]
c - 当前要用的字母 A-Z
*/
bool dfs(int id, char ch) {
  while (ans[id / n][id % n] != ' ') { // 跳过已经填好的
    id++;
  }
  if (id == n * n) {
    return true;
  }
  int sr = id / n;
  int sc = id % n; // update
  int ec = n;      // 当前列的枚举上界（后面用来剪枝）
  for (int r = sr; r < n; r++) {
    for (int c = sc; c < ec; c++) { // 以 (sr, sc) 为左上角
      if (ans[r][c] != ' ') {       // 剪枝 1: 遇到已填格子
        ec = c;                     // 封死右边界，不可再往右扩
        break;
      }
      int sum = (r - sr + 1) * (c - sc + 1);
      if (sum > 9) { // 剪枝 2: 面积
        ec = c;
        break;
      }
      int digit = 99; // 99 - 目前还没见过任何数字
      bool valid = true;
      for (int t = sr; t <= r; t++) {
        for (int i = sc; i <= c; i++) {
          if (seat[t][i] != '.') {
            if (digit != 99) { // 已经见过第一个数字
              valid = false;
              break;
            }
            digit = seat[t][i] - '0';
          }
        }
        if (!valid)
          break;
      }
      if (!valid) {
        ec = c;
        break;
      }
      if (digit < sum) { // 面积过大
        ec = c;
        break;
      }
      if (digit > sum) {
        continue;
      }
      for (int t = sr; t <= r; t++) {
        for (int i = sc; i <= c; i++) {
          ans[t][i] = ch;
        }
      }
      if (dfs(id + c - sc + 1, ch + 1)) {
        return true;
      }
      for (int t = sr; t <= r; t++) {
        for (int i = sc; i <= c; i++) {
          ans[t][i] = ' ';
        }
      }
    }
  }

  return false;
}
int main() {
  while (scanf("%d %d", &n, &K) && n) {
    memset(ans, ' ', sizeof(ans));
    for (int i = 0; i < n; i++) {
      scanf("%s", seat[i]);
    }
    dfs(0, 'A');
    for (int r = 0; r < n; r++) {
      for (int c = 0; c < n; c++) {
        printf("%c", ans[r][c]);
      }
      printf("\n");
    }
  }
}