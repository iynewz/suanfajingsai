// https://onlinejudge.org/external/15/1533.pdf
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;
int target; // 初始空位

struct State {
  int bitmask;                 // 棋盘状态
  int num;                     // 当前棋子数量
  int dist;                    // 走了几步
  vector<pair<int, int>> path; // 记录路径的 from, to
};

bool visited[1 << 15];

// 顺时针方向：左上，右上，右，左下，右下，左
int direction[15][6] = {
    {-1, -1, -1, 3, 2, -1}, {-1, 1, 3, 5, 4, -1},    {1, -1, -1, 6, 5, 2},
    {-1, 2, 5, 8, 7, -1},   {2, 3, 6, 9, 8, 4},      {3, -1, -1, 10, 9, 5},
    {-1, 4, 8, 12, 11, -1}, {4, 5, 9, 13, 12, 7},    {5, 6, 10, 14, 13, 8},
    {6, -1, -1, 15, 14, 9}, {-1, 7, 12, -1, -1, -1}, {7, 8, 13, -1, -1, 11},
    {8, 9, 14, -1, -1, 12}, {9, 10, 15, -1, -1, 13}, {10, -1, -1, -1, -1, 14}};

// 按字典序最小的，应为：左上，右上，左，右，左下，右下
// 都可以
// int direction[15][6] = {
//     {-1, -1, -1, -1, 2, 3}, {-1, 1, -1, 3, 4, 5},    {1, -1, 2, -1, 5, 6},
//     {-1, 2, -1, 5, 7, 8},   {2, 3, 4, 6, 8, 9},      {3, -1, 5, -1, 9, 10},
//     {-1, 4, -1, 8, 11, 12}, {4, 5, 7, 9, 12, 13},    {5, 6, 8, 10, 13, 14},
//     {6, -1, 9, -1, 14, 15}, {-1, 7, -1, 12, -1, -1}, {7, 8, 11, 13, -1, -1},
//     {8, 9, 12, 14, -1, -1}, {9, 10, 13, 15, -1, -1}, {10, -1, 14, -1, -1,
//     -1}};

bool isValid(const State &s) {
  if (s.num == 1 && s.bitmask == (1 << (target - 1))) {
    return true;
  }
  return false;
}
bool hasPeg(const int &bitmask, const int &pos) {
  return (bitmask & (1 << (pos - 1))) != 0;
}

/**
判断一次跳跃是否合法
to - 跳到哪里
captured - 要删除的中间棋子
*/
bool isLegalMove(const int &bitmask, const int &from, const int &dir, int &to,
                 vector<int> &captured) {
  vector<int> temp; // 临时存储被吃棋子
  int cur = from;

  while (true) {
    int next = direction[cur - 1][dir]; // cur-1 !!
    if (next == -1) {
      break;
    }
    if (hasPeg(bitmask, next) == false) { // next 是空位
      if (temp.empty()) {
        break;
      } else {
        to = next;
        captured = temp;
        return true;
      }
    } else {
      // printf("---from: %d next:%d\n", from, next);
      temp.push_back(next);
      cur = next;
    }
  }
  return false;
}

void bfs(State start) {
  queue<State> q;
  q.push((start));
  visited[start.bitmask] = true;

  while (!q.empty()) {
    State cur = q.front();
    q.pop();
    // 1. 判断是否是目标状态
    if (isValid(cur)) {
      printf("%d\n", cur.dist);
      printf("%d %d", cur.path[0].first, cur.path[0].second);
      for (int i = 1; i < cur.path.size(); i++) {
        printf(" %d %d", cur.path[i].first, cur.path[i].second);
      }

      printf("\n");
      return;
    }
    // 2. 枚举所有合法跳法
    for (int from = 1; from <= 15; from++) {
      if (hasPeg(cur.bitmask, from) == false) {
        continue;
      }

      // 每一个点的每一个 legal move
      for (int dir = 0; dir <= 5; dir++) {
        int to;
        vector<int> captured;
        if (isLegalMove(cur.bitmask, from, dir, to, captured)) {
          // 3. 生成 next.bitmask
          State next = cur;
          int tmpMask = cur.bitmask & (~(1 << (from - 1)));
          //  tmpMask = cur.bitmask | (1 << (to - 1)); //写错了 呜呜呜
          tmpMask |= (1 << (to - 1));
          for (int p : captured) { // 途径的都删掉
            tmpMask &= ~(1 << (p - 1));
          }
          next.bitmask = tmpMask;
          next.num -= captured.size();
          next.dist += 1;
          next.path.push_back({from, to});

          // 4. 如果没 visited，入队
          if (!visited[tmpMask]) {
            visited[tmpMask] = true;
            q.push(next);
          }
        }
      }
    }
  }
  printf("IMPOSSIBLE\n");
  return;
}
int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    memset(visited, false, sizeof(visited));

    scanf("%d", &target);
    State start;
    int tmp = (1 << 15) - 1; // 111...11, 15 个 1
    start.bitmask = tmp ^ (1 << (target - 1));
    start.num = 14;
    start.dist = 0;
    bfs(start);
  }
  return 0;
}
