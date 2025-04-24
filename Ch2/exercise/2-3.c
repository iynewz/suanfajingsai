#include<stdio.h>
int main() 
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int tree_num = 2 * n - 1 - 2 * (i - 1);  
            for(int j = 0; j < i; j++){
                printf(" "); // space
            }
            for(int j = 1; j <= tree_num; j++){
                printf("#"); // i 个 #
            }       
            for(int j = 0; j < i; j++){
                printf(" "); // space
            }
            printf("\n"); // new line
        }
    return 0;
}