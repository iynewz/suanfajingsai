//Puzzle, Uva227
#include <stdio.h>
#include <ctype.h>
#define SIZE 5

int main() {
    int puzzle_num = 0;
    char grid[SIZE][SIZE];
    int c;

    while (1) {
        int space_i = -1, space_j = -1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // 跳过换行符和其他空白
                do {
                    c = getchar();
                    if (c == 'Z' && i == 0 && j == 0) return 0; // 终止条件
                } while (c == '\n' || c == '\r'); // 关键修改：跳过换行符

                grid[i][j] = c;
                if (c == ' ') {
                    space_i = i;
                    space_j = j;
                }
            }
            // 清空当前行剩余输入（包括换行符）
            while ((c = getchar()) != '\n' && c != EOF);
        }

        // 打印调试信息
        printf("space:%d %d\n", space_i, space_j);
        printf("Puzzle #%d:\n", ++puzzle_num);
        for (int p = 0; p < SIZE; p++) {
            for (int q = 0; q < SIZE; q++) {
                printf("%c ", grid[p][q]); // 添加空格分隔符
            }
            printf("\n");
        }
    }
    return 0;
}