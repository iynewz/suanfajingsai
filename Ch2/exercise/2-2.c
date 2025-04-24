#include<stdio.h>
int main() 
{
    int a, b, c, case_num = 1;
    while(scanf("%d%d%d", &a, &b, &c) == 3) {
        int find = 0;
        for(int i = 10; i <= 100; i++) {
            if(i % 3 == a && i % 5  == b && i % 7 == c) {
                printf("Case %d: %d\n", case_num, i);
                case_num++;
                find = 1;
            }
        }
        if(find == 0) {
            printf("Case %d: No answer\n", case_num);
        }
        
    }
    return 0;
}