//4-1 Xiangqi, Uva1589
#include<stdio.h>
#include<string.h>
#include<cmath>
#include <iostream>
#include <fstream>

#define maxn 12

char board[maxn][maxn], c;
int b_g_r, b_g_c; //current black general position( row and column)
int red_g_r, red_g_c; //red general position(row and column)
// 可能的四个移动方向
int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

// 判断两将是否直接照面（中间无棋子）
int is_face_to_face(int r, int c) {
    if (c != red_g_c) return 0; // 不在同一列
    for (int i = r + 1; i < red_g_r; i++) {
        if (board[i][c] != 0) return 0; // 中间有其他红棋子
    }
    return 1;
}

int obstacle_count_between(int r, int c, int i, int j) {
    int obstacle = 0;
    if (j == c) { // 同一列
        if (abs(i - r) <= 1) return 0; // 太近了，中间不具备隔一个的条件
        int k = r < i ? r + 1 : r - 1;
        while (k != i) {
            if (board[k][j] != 0) {
                obstacle++;
            }
            r < i ? k++ : k--;
        }
    } else if (i == r) {
        if (abs(c - j) <= 1) return 0; // 中间不具备隔一个的条件
        int p = c < j ? c + 1 : c - 1;
        while (p != j) {
            if (board[i][p] != 0) {
                obstacle++;
            }
            j > c ? p++ : p--;
        }
    }
    return obstacle;
}

int horse_attack(int r, int c, int i, int j) { // check if the horse (i, j) can attack (r, c)
    int x = abs(j - c), y = abs(i - r);
    // printf("enter horse_attack, r%d c%d, i%d j%d, x%d y%d\n", r, c, i, j, x, y);
    if (x == 1 && y == 2) {
        if ((r < i && board[i-1][j] == 0) || (r > i && board[i+1][j] == 0)) {
            return 1;
        }
    } else if(x == 2 && y == 1) {
        if ((c < j && board[i][j - 1] == 0) || (c > j && board[i][j + 1] == 0)) {
            return 1;
        }
    }
    return 0;
}

// 判断黑将位置 (r,c) 是(1)否(0)被红方棋子攻击
int is_attacked(int r, int c) {
    if (is_face_to_face(r, c)) {
        return 1;
    }
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i == r && j == c && board[i][j] != 0) { //这个地方已经被黑将占领
                continue;
            }
            if (board[i][j] == 'R' && (i == r || j == c)) { //如果横竖存在 车 R
                if (obstacle_count_between(r, c, i, j) == 0) {
                    return 1;
                }
                
            }
            if (board[i][j] == 'C' && (i == r || j == c)) {
                // printf("(%d, %d) is 炮 C\n", i, j);
                if (obstacle_count_between(r, c, i, j) == 1) {
                    return 1;
                }   
            }
            if (board[i][j] == 'H' && horse_attack(r, c, i, j)) { //如果存在 马 H 的攻击
                return 1;
            }

        }
    }
    return 0;
}

// 判断是否将死
int is_checkmate() {
    for (int i = 0; i < 4; i++) {
        int b_g_r_new = b_g_r + dir[i][0]; //after possible move
        int b_g_c_new = b_g_c + dir[i][1];
        if (b_g_r_new >= 1 && b_g_r_new <= 3 && b_g_c_new >= 4 && b_g_c_new <= 6) {
            // printf("position(%d, %d) is attacked?  %d\n", b_g_r_new, b_g_c_new, is_attacked(b_g_r_new, b_g_c_new));
            // check if is attacked
            if (!is_attacked(b_g_r_new, b_g_c_new)) {
                return 0; // 只要有存在安全位置， 提前 return 0
            } 
        } else continue;
    }
    return 1;
}


int main() {
    for (;;) {
        int red_count;
        scanf("%d%d%d", &red_count, &b_g_r, &b_g_c);
        if (red_count == 0) {
            break;
        }
        memset(board, 0, sizeof(board));
        for (int i = 0; i < red_count; i++) {
            char c;
            int x, y;
            scanf(" %c", &c);
            scanf("%d%d", &x, &y);
            board[x][y] = c;
            if (c == 'G') {
                red_g_r = x;
                red_g_c = y;
            }
        }
        if (is_checkmate()) {
            printf("YES"); // 将死
        } else {
            printf("NO"); 
        }
        printf("\n");

    }
  
    return 0;
}

