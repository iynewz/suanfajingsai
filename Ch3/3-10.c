//Circular Sequence, Uva 1584
#include<stdio.h>
#include<string.h>
#define maxn 105

int main() {
    int T;
    scanf("%d", &T);
    char s[maxn];
    while(T--) {
        scanf("%s", s);
        int min_head = 0; // suppose the initial min sequence start from s[0]. 
    // update this value.
        int len = strlen(s);
        for (int head = 1; head < len; head++) { // head 从 1 开始，因为 min_head 初始是 0
            int is_smaller = 0; // 标记 head 是否比 min_head 更小
            for (int k = 0; k < len; k++) { // 逐字符比较
                char current_char = s[(head + k) % len];
                char min_char = s[(min_head + k) % len];
                if (current_char < min_char) {
                    is_smaller = 1; // head 更小
                    break;
                } else if (current_char > min_char) {
                    break; // head 更大，无需继续比较
                }
                // 如果字符相等，继续比较下一个字符
            }
            if (is_smaller) {
                min_head = head; // 更新最小起始位置
            }
        }
    // printf("%d\n", min_head);
        for (int i = 0; i < len; i++) {
            printf("%c", s[(min_head + i) % len]);
        }
        printf("\n");
    }
    return 0;
}