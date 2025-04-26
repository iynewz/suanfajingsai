//WERTYU, Uva 10082
#include<stdio.h>
#include<string.h>
char key[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
int main() {
    int i, c;
    while((c = getchar()) != EOF) {
        // 查找字符 c 在 key 中的位置
        char *p = strchr(key, c);
        printf("%p\n", p);   // 输出 p 的地址: e.g. 0x104de8001
        printf("%c\n", *p); // 输出 p 指向的值
        printf("%c\n", *(p - 1)); 

        if (p != NULL) { // Be careful of Segmentation Fault
            putchar(*(p - 1)); 
        } else {
            putchar(c); // 如未找到，原样输出
        }
    }
    return 0;
}
