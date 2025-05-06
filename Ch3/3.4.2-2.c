#include<stdio.h>
#include<string.h>
#define maxn 10000000 + 10

static char s[maxn]; // 静态存储区（或全局变量）


int main() {
    // char s[maxn];
    scanf("%s", s);
    int tot = 0;
    int len = strlen(s);
    for(int i = 0; i < len; i++) {
        if(s[i] == '1') {
            tot++;
        }
    }
    printf("%d\n", tot);
    return 0;
}