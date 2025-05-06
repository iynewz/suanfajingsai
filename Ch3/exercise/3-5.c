//Puzzle, Uva227
#include<stdio.h>
#include <ctype.h>
#define size 5


int main() {
    int puzzle_count = 0;
    char grid[size][size];
    int i, j;
    int space_i = -1, space_j = -1;
    while(1){
        // read puzzle input
        for(i = 0; i < size; i++) {
            for(j = 0; j < size; j++) {
                char c;

                c = getchar(); 
                if(c == 'Z' && i == 0 && j == 0) {
                    return 0;
                }
                if(c == ' ') {
                    space_i = i;
                    space_j = j;
                }
                grid[i][j] = c;
            }
            getchar(); // skip the \n'
        }
        // printf("space:%d, %d\n", space_i, space_j);
        // read move input
        int valid = 1;
        int new_i = space_i, new_j = space_j;
        char ch;
        
        while((ch = getchar()) != '0') {
            // printf("move:%c\n", ch);
            if(ch == '\n') continue; 
            
            // calculate new position
            int tmp_i = new_i, tmp_j = new_j;
            if(ch == 'A') {
                tmp_i--;
            } else if (ch == 'B') {
                tmp_i++;
            } else if (ch == 'L') {
                tmp_j--;
            } else if (ch == 'R') {
                tmp_j++;
            } else {
                valid = 0;
            }

            if(tmp_i < 0 || tmp_i >= size || tmp_j < 0 || tmp_j >= size) {
                valid = 0;
            }

            if (valid) {
                grid[new_i][new_j] = grid[tmp_i][tmp_j];
                grid[tmp_i][tmp_j] = ' ';
                new_i = tmp_i;
                new_j = tmp_j;
            }
        }
        getchar(); // skip the '\n' after '0'

        if(puzzle_count > 0) {
            printf("\n");
        }
        printf("Puzzle #%d:\n", ++puzzle_count);
        int p, q;
        if(valid) {
            for(p = 0; p < size; p++) {
                for(q = 0; q < size; q++) {
                    printf("%c", grid[p][q]);
                    if(q < size - 1) {
                     printf(" ");
                    }
                }
                printf("\n");
            }
        } else {
            printf("This puzzle has no final configuration.\n");
        }
    }
    return 0;
}