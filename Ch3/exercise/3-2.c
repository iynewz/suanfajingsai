//Molar Mass, Uva1586
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define maxn 85

const double C = 12.01, H = 1.008, O = 16.00, N = 14.01;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        char s[maxn];
        scanf("%s", s);
        double sum = 0.0;
        int len = strlen(s);
        int i = 0;
        while (i < len) {
            double weight = 0.0;
            
            if(s[i] == 'C') {
                weight = C;
            } else if(s[i] == 'H') {
                weight = H;
            } else if(s[i] == 'O') {
                weight = O;
            } else if(s[i] == 'N') {
                weight = N;
            }

            i++;
            int count = 0;
            while(i < len && isdigit(s[i]) == 1) {
                count = count * 10 + (s[i] - '0');
                i++;
            }
            if(count == 0) {
                count = 1;
            }
            sum = sum + weight * count;
        }
        printf("%.3f\n", sum);
    }
    return 0;
}