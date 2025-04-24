#include<stdio.h>
int main() {
    
    for(int j = 123; j < 345; j++) {
        int x = j;
        int y = 2 * j;
        int z = 3 * j;
        int a = x / 100;
        int b = (x - 100 * a) / 10;
        int c = x % 10;
        int d = y / 100;
        int e = (y - 100 * d) / 10;
        int f = y % 10;
        int g = z / 100;
        int h = (z - 100 * g) / 10;
        int i = z % 10;
        int sum_9 = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9;
        int multi_9 =  1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9;
        if(a + b + c + d + e + f + g + h + i == sum_9 && a * b * c * d * e * f * g * h * i == multi_9) {
            printf("%d %d %d\n", x, y, z);
        }
    }
    return 0;
}
