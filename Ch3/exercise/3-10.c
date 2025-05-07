//Box, UVa1587
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

// 比较函数：先按 row[0] 升序，若相同则按 row[1] 升序
int compare(const void *a, const void *b) {
    const int *rowA = (const int *)a;
    const int *rowB = (const int *)b;
    
    if (rowA[0] != rowB[0]) {  // 先比较第一个元素
        return rowA[0] - rowB[0];
    } else {  // 第一个元素相同，比较第二个元素
        return rowA[1] - rowB[1];
    }
}

int main() {
    int a, b;
    int i = 0;
    int grid[6][2];
    while(1) {
        for(int i = 0; i < 6; i++) {
            if (scanf("%d %d", &grid[i][0], &grid[i][1]) != 2) {
                return 0;
            }
            if (grid[i][1] < grid[i][0]) {
                int smaller = grid[i][1];
                grid[i][1] = grid[i][0];
                grid[i][0] = smaller;
            }
        }

        
            
        // sort grid[i][0] from small to large
        qsort(grid, 6, sizeof(grid[0]), compare);

        // for(int i = 0; i < 6; i++) {
        //     for(int j = 0; j < 2; j++) {
        //         printf("%d ", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        if(grid[0][0] == grid[1][0] && grid[0][1] == grid[1][1] 
        && grid[2][0] == grid[3][0] && grid[2][1] == grid[3][1]
        && grid[4][0] == grid[5][0] && grid[4][1] == grid[5][1]
        && grid[0][0] == grid[2][0] && grid[0][1] == grid[4][0]
        && grid[2][1] == grid[4][1]
        ) {
            printf("POSSIBLE\n");
        } else {
            printf("IMPOSSIBLE\n");
        }

    }
    return 0;
}