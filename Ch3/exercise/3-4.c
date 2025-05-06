//Periodic Strings, Uva455
#include<stdio.h>
#include<string.h>

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        char s[85];
        scanf("%s", s);
        int len = strlen(s);
        int i;
        for(i = 0; i < len; i++) {
            int k = i + 1;
            if(len % k != 0) {
                continue; //break 会直接跳出外层循环，导致后面的 k 不再被检查，而实际上可能有更大的 k 满足条件
            }
            int j;
            int valid = 1;
            for(j = k; j < len; j++) {
                if(s[j] != s[j%k]) {
                    valid = 0;
                    break;
                }
            }
            if(valid) {
                printf("%d\n", k);
                break;
            }
        }
        if (T) printf("\n");  
    }
    return 0;

}