// print trace not correct
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int T;
int n, m, s, t; // the number of vertices, the number of obstacles and the label
                // of the source and target.
vector<vector<int>> adj; // edges
struct State {
  int robot; // 机器人所在结点 [0..n-1]
  int stone; // 石头位置 bitmask
};
const int maxn = 15 + 2;
bool visited[maxn][1 << maxn];
State parent[maxn][1 << maxn];
State endState;

int bfs(State start) {
  queue<pair<State, int>> q;
  q.push({start, 0});
  visited[start.robot][start.stone] = true;
  parent[start.robot][start.stone] = {-1, -1};

  while (!q.empty()) {
    State cur = q.front().first;
    int dist = q.front().second;
    q.pop();

    // if reach target
    if (cur.robot == t) {
      endState = cur;
      return dist;
    }
    int r = cur.robot;
    int mask = cur.stone;

    // move robot
    for (int v : adj[r]) {
      if (!((1 << v) & mask)) { // v: no stone

        if (!visited[v][mask]) {
          State next;
          next.robot = v;
          next.stone = mask;
          visited[v][mask] = true;
          q.push({next, dist + 1});
          parent[v][mask] = cur; // 当前状态是从哪个状态来的
        }
      }
    }
    // move stone
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) { // 遍历每一个 stone 位置
        for (int v : adj[i]) {
          if (!((1 << v) & mask) && v != r) { // v: no stone, no robot
            // move
            int newMask = (mask ^ (1 << i)) | (1 << v);
            if (!visited[r][newMask]) {
              State next;
              next.robot = r;
              next.stone = newMask;
              visited[r][newMask] = true;
              q.push({next, dist + 1});
              parent[r][newMask] = cur;
            }
          }
        }
      }
    }
  }
  return -1;
}

void printTrace(State end) {
  vector<State> path;

  State cur = end;
  while (!(cur.robot == -1 && cur.stone == -1)) {
    path.push_back(cur);

    State prev = parent[cur.robot][cur.stone];
    if (prev.robot == -1 && prev.stone == -1) {
      break;
    }

    cur = parent[cur.robot][cur.stone];
  }

  reverse(path.begin(), path.end());

  // for (auto &s : path) {
  //   printf("robot=%d stoneMask=%d\n", s.robot, s.stone);
  // }
  for (int i = 1; i < path.size(); i++) {
    State pre = path[i - 1];
    State now = path[i];

    // robot 动了
    if (pre.robot != now.robot) {
      printf("%d %d\n", pre.robot + 1, now.robot + 1);
      continue;
    }

    // robot 没动，obstacle 在动
    int from = -1, to = -1;

    for (int b = 0; b <= n; b++) {
      bool had = pre.stone & (1 << b);
      bool has = now.stone & (1 << b);
      // printf("--b:%d, had:%d, has:%d , pre.stone:%d, now.stone:%d\n", b, had,
      //        has, pre.stone, now.stone);
      if (had && !has) {
        from = b + 1; // 石头离开
      }
      if (!had && has) {
        to = b + 1; // 石头到达
      }
    }

    // 题目保证这是合法的一步
    printf("%d %d\n", from, to);
  }
}

int main() {
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    n--;
    s--;
    t--;

    adj.assign(maxn, vector<int>());
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < maxn; i++) {
      for (int j = 0; j < (1 << maxn); j++) {
        parent[i][j] = {-1, -1};
      }
    }

    int haveStone = 0;
    for (int i = 0; i < m; i++) {
      int tmp;
      scanf("%d", &tmp);
      tmp--; // 1-based
      haveStone = haveStone | (1 << tmp);
    }
    for (int i = 0; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--;
      v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    State start;
    start.robot = s;
    start.stone = haveStone;

    int ans = bfs(start);
    printf("Case %d: %d\n", kase, ans);
    printTrace(endState);
  }
  return 0;
}