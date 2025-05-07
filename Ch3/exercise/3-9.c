//All in All, UVa10340
#include<stdio.h>
#include<string.h>


int main() {
    char s[1000000], t[1000000];
    while (scanf("%s %s", s, t) != EOF) {
        int s_len = strlen(s), t_len = strlen(t);
        int valid = 0;
        int i = 0, j = 0;
        while(i < s_len &&  j < t_len) {
            if(s[i] == t[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        
        printf( i == s_len ? "Yes\n" : "No\n");
        
    }
    return 0;
}