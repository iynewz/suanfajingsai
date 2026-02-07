#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
int n, K;
const int maxn = 20 + 5;
char grid[maxn][maxn]; // g−1 个组已经放好的“最终状态”
int done = 0;          // 放了几个矩形了
struct Rectangle {
  int height;
  int width;
  int r1, c1; // 左上角
};
vector<Rectangle> options[26];
bool used[26]; // 哪些组已放

bool canPutRect(Rectangle rect) {
  for (int r = rect.r1; r <= rect.r1 + rect.height - 1; r++) {
    for (int c = rect.c1; c <= rect.c1 + rect.width - 1; c++) {
      // 数字和 '.' 可以，'A'-'Z' 不可以
      if (grid[r][c] >= 'A' && grid[r][c] <= 'Z') {
        return false;
      }
    }
  }
  return true;
}

void putRect(Rectangle rect, int g) {
  char mark = 'A' + g; // 用组编号标记

  for (int r = rect.r1; r <= rect.r1 + rect.height - 1; r++) {
    for (int c = rect.c1; c <= rect.c1 + rect.width - 1; c++) {
      grid[r][c] = mark;
    }
  }
}

void removeRect(Rectangle rect) {
  for (int r = rect.r1; r <= rect.r1 + rect.height - 1; r++) {
    for (int c = rect.c1; c <= rect.c1 + rect.width - 1; c++) {
      grid[r][c] = '.'; // 回到空
    }
  }
}
void printRect() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}
int chooseNextGroup() {
  int best = -1;
  int minCnt = 1e9;
  for (int g = 0; g < K; g++) {
    if (used[g]) {
      continue;
    }
    int cnt = 0;
    for (Rectangle rect : options[g]) {
      if (canPutRect(rect)) {
        cnt++;
      }
    }
    if (cnt < minCnt) {
      minCnt = cnt;
      best = g;
    }
  }
  return best;
}
/**
g = 当前要处理的组编号 */
void dfs(int g) {
  if (g == K) {
    printRect();
    return;
  }
  int group = chooseNextGroup();
  if (group == -1) {
    return;
  }
  used[group] = true;
  for (Rectangle rect : options[group]) {
    if (canPutRect(rect)) {

      // put Rect here
      putRect(rect, g);
      dfs(g + 1);
      // remove, 回溯
      removeRect(rect);
    }
  }
  used[group] = false;
};

/**
第 k 个组
组长坐标 (r, c)
组人数 size
push to options[k]
*/
void possibleRec(int groupId, int r, int c, int size) {
  for (int h = 1; h <= size; h++) {
    if (size % h != 0) {
      continue;
    }
    int w = size / h;

    for (int dr = 0; dr < h; dr++) {
      for (int dc = 0; dc < w; dc++) {
        // 左上角
        int r1 = r - dr;
        int c1 = c - dc;
        if (r1 < 0 || c1 < 0) {
          continue;
        }
        // 右下角
        int r2 = r1 + h - 1;
        int c2 = c1 + w - 1;
        if (r2 >= n || c2 >= n) {
          continue;
        }
        Rectangle rec;
        rec.height = h;
        rec.width = w;
        rec.r1 = r1;
        rec.c1 = c1;
        options[groupId].push_back(rec);
      }
    }
  }
  sort(options[groupId].begin(), options[groupId].end(),
       [](const Rectangle &a, const Rectangle &b) {
         return a.height * a.width > b.height * b.width;
       });
}

/* for test */
void printPossibleRec(int groupId, int leader_r, int leader_c) {
  cout << "Group " << groupId
       << " possible rectangles: " << options[groupId].size() << endl;

  for (int i = 0; i < (int)options[groupId].size(); i++) {
    auto &rec = options[groupId][i];

    int top = rec.r1;
    int left = rec.c1;
    int bottom = top + rec.height - 1;
    int right = left + rec.width - 1;

    cout << "  #" << i << ": ";
    cout << "top-left=(" << top << "," << left << "), ";
    cout << "h=" << rec.height << ", w=" << rec.width;
    cout << " | covers r:[" << top << "," << bottom << "]";
    cout << " c:[" << left << "," << right << "]";

    // 检查是否包含组长
    bool contain = (leader_r >= top && leader_r <= bottom && leader_c >= left &&
                    leader_c <= right);

    cout << " | leader inside? " << (contain ? "YES" : "NO");

    cout << endl;
  }

  cout << endl;
}

int main() {

  while (cin >> n >> K && n != 0) {
    memset(grid, -1, sizeof(grid));
    for (int i = 0; i < 26; i++) {
      options[i].clear();
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char tmp;
        cin >> tmp;
        grid[i][j] = tmp;
      }
    }

    // 预处理
    int k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] != '.') {
          int size = grid[i][j] - '0';
          possibleRec(k, i, j, size);
          // printPossibleRec(k, i, j);
          k++;
          grid[i][j] = '.';
        }
      }
    }

    dfs(0);
  }

  return 0;
}