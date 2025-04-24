#include<stdio.h>
#include<string.h>

int main() {
    int count = 0;
    char s[20], buf[99];
    scanf("%s", s);
    for(int i = 111; i <= 999; i++) {
        for(int j = 11; j <= 99; j++) {
            int line_1 = i * (j % 10);
            int line_2 = i * (j / 10);
            int ans = i * j;

            sprintf(buf, "%d%d%d%d%d", i, j, line_1, line_2, ans);
            int ok = 1;
            for(int i = 0; i < strlen(buf); i++) {
                if(strchr(s, buf[i]) == NULL) {
                    ok = 0;
                }
            }

            if(ok) {
                count++;
                printf("<%d>\n", count);
                
                printf("%5d\nX%4d\n-----\n%5d\n%4d\n-----\n%5d\n\n", i, j, line_1, line_2, ans);
            }
        }
    }
    printf("The number of solutions = %d\n", count);
    return 0;
}