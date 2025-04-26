// Palindrome, Uva 401
#include<stdio.h>
#include<string.h>
#include<ctype.h>
const char* rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"is not a palindrome.", "is a regular palindrome.", "is a mirrored string.", "is a mirrored palindrome"};

char find_mirrored_char(char ch){
    // 'A' - 'A' -> 0
    // 'B' - 'A' -> 1
    // '0' - 'A' -> -17
    // '1' - 'A' -> -16
    //  printf("%c\n", rev[ch - 'A']);
    return isalpha(ch) ? rev[ch - 'A'] : rev[ch - '0' + 25];
}

int main() {
    char s[50];
    while(scanf("%s", s) == 1) {
        int len = strlen(s);
        int p = 1, m = 1;
        for(int i = 0; i < len / 2; i++) {
            // test if is palindrome
            if(s[i] != s[len-1-i]) {
                p = 0;
            }
            // test if is mirror
            if(s[i] != find_mirrored_char(s[len-1-i])) {
                m = 0;
            }
        }
        if(p == 0 && m == 0){
        printf("%s is %s\n", s, msg[0]);
        }
        if(p == 1 && m == 0){
        printf("%s is %s\n", s, msg[1]);
        }
        if(p == 0 && m == 1){
        printf("%s is %s\n", s, msg[2]);
        }
        if(p == 1 && m == 1){
        printf("%s is %s\n", s, msg[3]);
        }
    }
    return 0;
}