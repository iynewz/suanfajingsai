// learn from https://www.cnblogs.com/pfypfy/p/9062584.html
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 5000 + 5;
int n;
bool selected[maxn];
struct Block {
  int xl, yl, xr, yr; //(xl, yl), (xr, yr)
  int num;
  int ansx, ansy;
} blocks[maxn];

bool cmpByNum(const Block &a, const Block &b) { return a.num < b.num; }
bool cmpByXr(const Block &a, const Block &b) { return a.xr < b.xr; }
bool cmpByYr(const Block &a, const Block &b) { return a.yr < b.yr; }

void read() {
  for (int i = 1; i <= n; i++) {
    cin >> blocks[i].xl >> blocks[i].yl >> blocks[i].xr >> blocks[i].yr;
    blocks[i].num = i;
  }
}
bool solve() {

  memset(selected, false, sizeof(selected));

  // 按 xr 排序
  sort(blocks + 1, blocks + n + 1, cmpByXr);

  for (int i = 1; i <= n; i++) {
    int x = blocks[i].xl;
    while (selected[x] && x <= blocks[i].xr) {
      x++;
    }
    if (x > blocks[i].xr) {
      return false;
    } else {
      selected[x] = true;
      blocks[i].ansx = x;
    }
  }

  memset(selected, false, sizeof(selected));
  sort(blocks + 1, blocks + n + 1, cmpByYr);
  for (int i = 1; i <= n; i++) {
    int y = blocks[i].yl;
    while (selected[y] && y <= blocks[i].yr) {
      y++;
    }
    if (y > blocks[i].yr) {
      return false;
    } else {
      selected[y] = true;
      blocks[i].ansy = y;
    }
  }
  return true;
}

void print_ans() {
  sort(blocks + 1, blocks + n + 1, cmpByNum);
  for (int i = 1; i <= n; i++) {
    cout << blocks[i].ansx << " " << blocks[i].ansy << endl;
  }
}

int main() {

  while (cin >> n && n) {
    read();
    if (solve()) {
      print_ans();

    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }
  return 0;
}