// Message Decoding, Uva 213
#include<stdio.h>

#define MAX_LEN 21
int queue[MAX_LEN];
int n;

int out(int position, int step, int direction) { //0, 4, 1
    int p = position; //9
    if (direction) {
        while (step) { // 4,3,2,1
            p = (p + 1) % n; //0,1,2,3
            while (queue[p] == 0) {
                p = (p + 1) % n;
            }
            step--;
        }
    } else { //顺时针
        while (step) { //4,3
            p = (p - 1 + n) % n;//9
            while (queue[p] == 0) {
                p = (p - 1 + n) % n;
            }
            step--;
        }
    }
    return p ;

}

int main() {
    int k, m;
    
    while (scanf("%d%d%d", &n, &k, &m) == 3 && n != 0) {
        for (int i = 0; i < n; i++) {
            queue[i] = i + 1;
        }
        int left = n;
        int p_A = n - 1, p_B = 0;

        while (left) {
            p_A = out(p_A, k, 1);  // update pointer A
            p_B = out(p_B, m, 0); // update pointer A
            // printf("p_A: %d", p_A);
            // printf("p_B: %d", p_B);
            printf("%3d", queue[p_A]);
            left--;
            if (queue[p_A] != queue[p_B]) {
                printf("%3d", queue[p_B]);
                left--;
            }
            if (left) {
                printf(",");
            }
            queue[p_A] = 0;
            queue[p_B] = 0;
        }
        printf("\n");
    }
    return 0;
}