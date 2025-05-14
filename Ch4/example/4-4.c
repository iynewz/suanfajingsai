// 4-3 The Dole Queue, UVa 133
#include<stdio.h>
#include<string.h>

int code[8][255];

// char readchar() {
//     while (1) {
//         char ch = getchar();
//         if (ch == '\n') {
//             break;
//         }
//         return ch;
//     }
// }
char readchar() {
    for (; ;) {
        char ch = getchar();
        if (ch != '\n' && ch != '\r') {
            return ch;
        }
    }
}

int readint(int c) { //读取 c 位二进制并转换成十进制
    int v = 0;
    while(c--) {
        v = v * 2 + readchar() - '0';
    }
    return v;
}

int readcodes() {
    memset(code, 0, sizeof(code));
    code[1][0] = readchar();
    for (int i = 2; i <= 7; i++) {
        for(int j = 0; j < (1 << i) - 1; j++) {
            int ch = getchar();
            // printf("read ch: %c\n", ch);
            if (ch == EOF) {
                return 0;
            }
            if (ch == '\n') {
                return 1; // 为什么是1，不应该是 0 吗？读到换行符，停下？
            } else {
                code[i][j] = ch;
            }
            
        }
    }
    return 1;
}

int printcodes() {
    for (int i = 1; i <= 7; i++) {
        for(int j = 0; j < (1 << i) - 1; j++) {
            printf("%c", code[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    while (readcodes()) {
        // printcodes();
        for (;;) {
            int len = readint(3); // 读取3位二进制长度
            if (len == 0) {
                break;
            }
            for (;;) {
                int value = readint(len);
                if (value == (1 << len) - 1) {
                    break; // 全1码结束当前长度
                }
                putchar(code[len][value]);
            }
        }
        putchar('\n');
       
    }
    return 0;
}