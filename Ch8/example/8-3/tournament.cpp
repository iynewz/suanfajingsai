#include <iostream>
using namespace std;
const int maxn = 100 + 5;
int grid[maxn][maxn];

void schedule(int r, int c, int w) {
  if (w == 1) {
    grid[1][1] = 1;

    return;
  }
  int curr_w = w / 2;
  cout << "curr_w: " << curr_w << endl;
  grid[r + curr_w][c + curr_w] = grid[r][c];
  grid[r + curr_w][c] = grid[r][c] + curr_w;
  grid[r][c + curr_w] = grid[r + curr_w][c];

  // left top
  schedule(r, c, curr_w);
  // right top
  schedule(r, c + curr_w, curr_w);
  // left down
  schedule(r + curr_w, c, curr_w);
  // right down
  schedule(r + curr_w, c + curr_w, curr_w);
}
int main() {
  int k;
  cin >> k;
  int width = 1;
  for (int i = 1; i <= k; i++) {
    width *= 2;
  }
  cout << "width: " << width << endl;
  schedule(1, 1, width);
  for (int i = 1; i <= width; i++) {
    for (int j = 1; j <= width; j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}