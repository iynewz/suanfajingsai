// TLE, Then i learned from https://www.cnblogs.com/UniqueColor/p/4872790.htm.
// Now AC
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>

using namespace std;
int R, C;
const int maxn = 15 + 5;
char grid[maxn][maxn];
bool visited[maxn][maxn];     // for dfs
bool visited_bfs[maxn][maxn]; // for bfs
int dir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int possible[30 + 5];
string best = "";

bool isBetter(const string &a, const string &b) {
  if (a.length() != b.length()) {
    return a.length() > b.length();
  }
  return a > b;
}

bool not_in_border(int r, int c) { return r < 0 || r >= R || c < 0 || c >= C; }

int bfs(int r, int c) {
  memset(visited_bfs, false, sizeof(visited_bfs));
  memset(possible, -1, sizeof(possible));

  queue<int> q;
  visited_bfs[r][c] = true;
  q.push(r * C + c);
  int length = 0;
  while (!q.empty()) {
    int tmp = q.front();
    q.pop();
    int cur_r = tmp / C;
    int cur_c = tmp % C;

    // cout << "--" << cur_r << r << "--" << cur_c << c << endl;
    for (int i = 0; i < 4; i++) {
      int new_r = cur_r + dir[i][0];
      int new_c = cur_c + dir[i][1];
      if (not_in_border(new_r, new_c)) {
        continue;
      }
      if (grid[new_r][new_c] == '#') {
        continue;
      }
      if (visited[new_r][new_c] || visited_bfs[new_r][new_c]) {
        continue;
      }

      possible[length++] = grid[new_r][new_c] - '0';
      visited_bfs[new_r][new_c] = true;
      q.push(new_r * C + new_c);
    }
  }
  return length;
}

void dfs(int r, int c, string cur) {
  int upper_bound = bfs(r, c);
  if (upper_bound + cur.length() < best.length()) {
    return;
  }
  if (upper_bound + cur.length() == best.length()) {
    sort(possible, possible + upper_bound); // 从小到大
    // cout << "possible: ";
    // for (int i = 0; i < upper_bound; i++) {
    //   cout << possible[i] << " ";
    // }
    // cout << endl;
    string tmp = cur;
    for (int i = upper_bound - 1; i >= 0; i--) {
      tmp += char(possible[i] + '0');
    }
    if (isBetter(best, tmp)) {
      return;
    }
  }

  //   cout << "cur " << cur << endl;
  visited[r][c] = true;

  for (int i = 0; i < 4; i++) {
    int newr = r + dir[i][0];
    int newc = c + dir[i][1];
    if (not_in_border(newr, newc)) {
      continue;
    }
    if (visited[newr][newc] || grid[newr][newc] == '#') {
      continue;
    }
    if (isBetter(cur + grid[newr][newc], best)) {
      best = cur + grid[newr][newc];
    }
    dfs(newr, newc, cur + grid[newr][newc]);
  }
  visited[r][c] = false;
}
int main() {

  while (scanf("%d %d", &R, &C) == 2 && R != 0) {
    // cout << R << "-" << C << endl;
    best = "";

    for (int r = 0; r < R; r++) {
      scanf("%s", grid[r]);
    }

    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
        if (grid[r][c] != '#') {
          memset(visited, false, sizeof(visited));
          string start = string(1, grid[r][c]);
          //   cout << "start " << start << endl;
          dfs(r, c, start);
        }
      }
    }
    cout << best << endl;
  }

  return 0;
}