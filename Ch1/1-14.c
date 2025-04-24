#include<stdio.h>
int main()
{
    int a, b, c, t;
    scanf("%d%d%d", &a, &b, &c);
    if(a > b) {t = a; a = b; b = t;} //switch a and b to make a <= b
    if(a > c) {t = a; a = c; c = t;} //switch a and c to make a <= c and da <= b
    if(b > c) {t = b; b = c; c = t;}
    printf("%d %d %d\n", a, b, c);
    return 0;
}
