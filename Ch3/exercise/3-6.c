//Crossword Answers, Uva227
#include<stdio.h>
#define size 10

int main() {
    int r, c;
    char grid[size][size];
    int puzzle_count = 0;

    while(scanf("%d", &r) == 1 && r != 0) {
        scanf("%d", &c);
        // Generate numbering
        int number[size][size] = {0};
        int current_num = 0;

        if(puzzle_count > 0) {
            printf("\n");
        }
        printf("puzzle #%d:\n", ++puzzle_count);
        
        for(int i = 0; i < r; i++) {
            scanf("%s", grid[i]);
            for(int j = 0; j < c; j++) {
                if(grid[i][j] == '*') {
                    continue; // skip the '*'
                }
                if(i == 0 || j == 0 || grid[i][j-1] == '*' || grid[i-1][j] == '*') {
                    current_num++;
                    number[i][j] = current_num;
                }
            }
        }

        printf("Across\n");
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c;) {
                if(number[i][j] == 0) {
                    j++;
                    continue; // skip '*' and other white cell. until we find the first starting cell.
                }
                printf("%3d.", number[i][j]);
                while(grid[i][j] != '*' && j < c) {
                    printf("%c",grid[i][j]);
                    j++;
                }
                printf("\n");
                
            }
        }

      // Print Down words
        printf("Down\n");
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if (number[i][j] == 0) {
                    continue;
                } else {
                    printf("%3d.", number[i][j]);
                    int k = i;
                    while(k < r && grid[k][j] != '*') {
                        printf("%c", grid[k][j]);
                        k++;
                        number[k][j] = 0; //set the already print cell state
                    }
                    printf("\n");
                }
               
            }
        }
    }

    return 0;
}