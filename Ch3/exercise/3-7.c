// DNA Consensus String, UVa1368
#include<stdio.h>

// Custom function to find the maximum of two numbers
int findMax(int b, int a) {

    // Return a if a is greater than or equal to b, else
    // return b
    return (a >= b) ? a : b;
}


int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int m, n;
        scanf("%d %d", &m, &n);
        char grid[m][n];

        for(int i = 0; i < m; i++) {
            scanf("%s", grid[i]);
        }

        // for(int i = 0; i < m; i++) {
        //     for(int j = 0; j < n; j++) {
        //         printf("%c", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("----");
        int dis = 0;
        for(int j = 0; j < n; j++) {
            int count_A = 0, count_C = 0, count_G = 0, count_T = 0;
            for(int i = 0; i < m; i++) {
                if(grid[i][j] == 'A') count_A++;
                if(grid[i][j] == 'C') count_C++;
                if(grid[i][j] == 'G') count_G++;
                if(grid[i][j] == 'T') count_T++;
            }
            int max = findMax(findMax(count_A, count_C),findMax(count_G, count_T));
            
            if(max == count_A) printf("A");
            else if(max == count_C) printf("C");
            else if(max == count_G) printf("G");
            else if(max == count_T) printf("T");
            dis += m - max;

        }
        printf("\n");
        printf("%d\n", dis);
    }
    return 0;
}