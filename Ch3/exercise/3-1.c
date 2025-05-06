// Score, Uva1585
#include<stdio.h>
#include<string.h>

#define maxn 85

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        char s[maxn];
        scanf("%s", s);
        int len = strlen(s);
        int score = 0;
        int curr_seq = 0;
        int i;
        for(i = 0; i < len; i++) {
            if(s[i] == 'X') {
                curr_seq = 0;
            } else if(s[i] == 'O') {
                curr_seq ++;
                score = score + curr_seq;
            }

        }
        printf("%d\n", score);
    }
    return 0;

}