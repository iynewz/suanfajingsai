//  Master-Mind Hints, Uva 340
#include<stdio.h>
#define maxn 1010


int main() {
    int len;
    int a[maxn], guess[maxn];
    int case_num = 1;
    while(scanf("%d", &len) == 1 && len != 0 ){
        printf("Game %d:\n", case_num++);
        // Input the given array
        for(int i = 0; i < len; i++){
            scanf("%d", &a[i]);
        }
        while(1) {
            // Input the guess array 
            int all_zero = 1;
            int A = 0, B = 0;
            for(int i = 0; i < len; i++){
                scanf("%d", &guess[i]);
                if(guess[i] != 0){
                    all_zero = 0;
                }
                //do something to get A and B
                if(guess[i] == a[i]) {
                    A++;
                }
                int sum = 0;
                for(int d = 1; d <= 9; d++) {
                    int c_a = 0, c_guess = 0;
                    for(int i = 0; i < len; i++) {
                        if(a[i] == d) {
                            c_a++;
                        }
                    }
                    for(int i = 0; i < len; i++) {
                        if(guess[i] == d) {
                            c_guess++;
                        }
                    }
                    int min = (c_a < c_guess) ? c_a : c_guess;
                    sum = sum + min;
                    B = sum - A;
                }
            }
            // Break the loop when the guess array is all zero
            if(all_zero) {
                printf("All zero!\n");
                break;
            }
        
            printf("(%d,%d)\n", A, B);
        }

    }
    return 0;
}
