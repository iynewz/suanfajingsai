#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 10 + 5;
int n, m;
int grid[maxn][maxn];
int maxd;
int kase = 0;
/*
vis[0][i] - row - 第 i 行是否已经被某个皇后控制
vis[1] - col
vis[2] - diag1 - 主对角线
vis[3] - diag2 - 副对角线
*/
int vis[4][maxn * 2];

bool validate() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      bool noControl =
          !vis[0][i] && !vis[1][j] && !vis[2][j - i + n] && !vis[3][i + j];
      if (grid[i][j] && noControl) {
        return false;
      }
    }
  }
  return true;
}

bool dfs(int d, int cur) {
  if (d == maxd) {
    if (validate()) {
      printf("Case %d: %d\n", ++kase, d);
      return true;
    } else
      return false;
  }
  // 从 cur 之后找一个位置放
  for (int pos = cur; pos < n * m; pos++) {
    int i = pos / m;
    int j = pos % m;
    int tmp0 = vis[0][i];
    int tmp1 = vis[1][j];
    int tmp2 = vis[2][j - i + n];
    int tmp3 = vis[3][i + j];
    vis[0][i] = vis[1][j] = vis[2][j - i + n] = vis[3][i + j] = 1;
    if (dfs(d + 1, pos)) {
      return true;
    }
    vis[0][i] = tmp0;
    vis[1][j] = tmp1;
    vis[2][j - i + n] = tmp2;
    vis[3][i + j] = tmp3;
  }
  return false;
}

int main() {
  while (scanf("%d", &n) && n) {
    memset(grid, 0, sizeof(grid));

    scanf("%d", &m);
    getchar(); // 吞掉 m 之后的换行符！！
    // input grid
    char ch;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%c", &ch);
        if (ch == 'X') {
          grid[i][j] = 1;
        }
      }
      getchar(); // 吞掉 一行 之后的换行符
    }
    // test
    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < m; j++) {
    //     printf("%d", grid[i][j]);
    //   }
    //   printf("\n");
    // }

    // dfs
    for (maxd = 0;; maxd++) {
      memset(vis, 0, sizeof(vis));
      if (dfs(0, 0)) {
        break;
      }
    }
  }
  return 0;
}