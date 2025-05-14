// 4-2 Hangman Judge, UVa 489
#include<stdio.h>
#include<string.h>

#define MAX_DIGIT 100

int left, chance; // 还要猜 left 个位置，错 chance 此后会输
char ans[MAX_DIGIT], guess[MAX_DIGIT];
int win, lose;

void guess_function(char ch) {
    int ans_len = strlen(ans);
    int find = 0;
    for (int i = 0; i < ans_len; i++) {
        if (ans[i] == ch) {
            left--;
            ans[i] = ' ';
            find = 1;
        }
    }
    if (find == 0) {
        chance--;
    }
    if (chance == 0) {
        lose = 1;
    } else if (left == 0) {
        win = 1;
    }
}

int main() {
    int round_count;
    while(scanf("%d", &round_count) == 1) {
        if(round_count == -1) {
            return 0;
        }
        printf("Round %d\n", round_count);
        
        scanf("%s %s", ans, guess);
        win = lose = 0;
        chance = 7;
        left = strlen(ans);
        int guess_len = strlen(guess);
        for (int i = 0; i < guess_len; i++) {
            guess_function(guess[i]);
            if (win || lose) {
                break;
            }
        }

        if (win) {
            printf("You win.\n");
        } else if (lose) {
            printf("You lose.\n");
        } else {
            printf("You chickened out.\n");
        }
    }
    return 0;
}