// TLE

#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

char target[8 + 1];

struct Cube {
  char f[6];
};

struct State {
  int grid[9];  // -1 表示空位，每个格子放哪个 cube（或 -1）
  Cube cube[8]; // 每个 cube 的朝向
  int empty;    // 空位位置
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 面编号
// 0 top, 1 bottom, 2 front, 3 back, 4 left, 5 right

Cube roll(const Cube &c, int dir) {
  Cube n = c;
  if (dir == 0) { // UP 向前滚
    n.f[0] = c.f[2];
    n.f[3] = c.f[0];
    n.f[1] = c.f[3];
    n.f[2] = c.f[1];
  } else if (dir == 1) { // DOWN
    n.f[0] = c.f[3];
    n.f[2] = c.f[0];
    n.f[1] = c.f[2];
    n.f[3] = c.f[1];
  } else if (dir == 2) { // LEFT
    n.f[0] = c.f[5];
    n.f[4] = c.f[0];
    n.f[1] = c.f[4];
    n.f[5] = c.f[1];
  } else { // RIGHT
    n.f[0] = c.f[4];
    n.f[5] = c.f[0];
    n.f[1] = c.f[5];
    n.f[4] = c.f[1];
  }
  return n;
}

string encode(const State &s) {
  string res;
  for (int i = 0; i < 9; i++) {
    res += char(s.grid[i] + 2); // -1 -> 1
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 6; j++)
      res += s.cube[i].f[j];
  }
  return res;
}

int bfs(State start) {

  queue<pair<State, int>> q;
  unordered_set<string> vis;

  q.push({start, 0});
  vis.insert(encode(start));

  while (!q.empty()) {
    State cur = q.front().first;
    int dist = q.front().second;

    q.pop();
    if (dist > 30) {
      continue; //   剪枝
    }

    bool ok = true;
    for (int i = 0; i < 9; i++) {
      if (target[i] == 'E') {
        if (cur.grid[i] != -1) {
          ok = false;
          break;
        }
      } else {
        if (cur.grid[i] == -1) {
          ok = false;
          break;
        }
        if (cur.cube[cur.grid[i]].f[0] != target[i]) {
          ok = false;
          break;
        }
      }
    }
    if (ok)
      return dist;

    int x = cur.empty / 3;
    int y = cur.empty % 3;

    for (int d = 0; d < 4; d++) {
      int nx = x + dx[d], ny = y + dy[d];
      if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
        continue;

      int ni = nx * 3 + ny;
      State nxt = cur;

      int cid = cur.grid[ni];
      nxt.grid[cur.empty] = cid;
      nxt.grid[ni] = -1;
      nxt.empty = ni;

      nxt.cube[cid] = roll(cur.cube[cid], d);

      string key = encode(nxt);
      if (!vis.count(key)) {
        vis.insert(key);
        q.push({nxt, dist + 1});
      }
    }
  }
  return -1;
}

int main() {
  int x, y;
  while (cin >> x >> y) {
    if (x == 0 && y == 0)
      break;

    State start;
    int idx = 0;

    // 初始状态
    start.empty = (y - 1) * 3 + (x - 1);

    for (int i = 0; i < 9; i++) {
      if (i == start.empty) {
        start.grid[i] = -1;
      } else {
        start.grid[i] = idx++;
      }
    }

    // 初始化朝向
    for (int i = 0; i < 8; i++) {
      start.cube[i].f[0] = 'W';
      start.cube[i].f[1] = 'W';
      start.cube[i].f[2] = 'R';
      start.cube[i].f[3] = 'R';
      start.cube[i].f[4] = 'B';
      start.cube[i].f[5] = 'B';
    }
    // 目标状态
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 3; i++) {
        char c;
        cin >> c;
        int cnt = j * 3 + i;
        target[cnt] = c;
      }
    }
    // 打印一下看看
    int ans = bfs(start);
    cout << ans << "\n";
  }
  return 0;
}
