#include<stdio.h>
int main() {
    int c;
    int flag = 1;
    while((c = getchar()) != EOF) {
        if(c == '"') {
            printf("%s", flag ? "``" : "’’");
            flag = !flag;
        } else {
            printf("%c", c);
        }
    }
    return 0;
}