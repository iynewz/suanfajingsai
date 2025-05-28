// Othello, UVa220
#include <cstdio>
#include <string.h>

#define board_size 9
char board[board_size][board_size];
char current_player = '-';

char get_opponent(char player)
{
    return (player == 'B') ? 'W' : 'B';
}

// 可能的 8 个移动方向
int direction[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

void print_board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void print_count()
{
    int count_B = 0, count_W = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != '-')
            {
                board[i][j] == 'B' ? count_B++ : count_W++;
            }
        }
    }
    printf("Black - %2d White - %2d\n", count_B, count_W);
}

int check_move(int r, int c, int need_flip)
{ // check if current player can move to (r, c)
    int can_move = 0;
    char opponent = get_opponent(current_player);
    for (int i = 0; i < 8; i++)
    { // 尝试向每一个方向移动直到：或满足落子条件，或溢出棋盘，或遇到空格
        int dr = direction[i][0], dc = direction[i][1];
        int opponent_count = 0;
        int meet_self_color = 0;
        int new_r = r + dr, new_c = c + dc;
        while (1)
        {
            if (new_r < 0 || new_r > 7 || new_c < 0 || new_c > 7 || board[new_r][new_c] == '-')
            {
                break;
            }
            if (board[new_r][new_c] == current_player)
            {
                meet_self_color = 1;
                break;
            }
            if (board[new_r][new_c] == opponent)
            {
                opponent_count++;
                new_r += dr;
                new_c += dc;
            }
        }
        if (opponent_count > 0 && meet_self_color == 1)
        { // 满足落子条件
            can_move = 1;
            if (need_flip)
            {
                for (int k = 1; k <= opponent_count; k++)
                {
                    board[r + dr * k][c + dc * k] = current_player;
                }
            }
        }
    }
    if (board[r][c] != '-')
    {
        can_move = 0;
    }
    return can_move;
}

void list_moves()
{
    int has_legal_move = 0;
    int is_first_move = 1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (check_move(i, j, 0))
            {
                has_legal_move = 1;

                if (!is_first_move)
                {
                    printf(" ");
                }
                printf("(%d,%d)", i + 1, j + 1);
                is_first_move = 0;
            }
        }
    }
    if (!has_legal_move)
    {
        printf("No legal move.");
    }
    printf("\n");
}

int main()
{
    int case_number;
    scanf("%d", &case_number);
    while (case_number--)
    {
        memset(board, 0, sizeof(board));
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                scanf(" %c", &board[i][j]); // 跳过所有空白字符, 包括换行符
            }
        }
        scanf(" %c", &current_player);
        // read the commands until "Q"
        char command[4];
        while (1)
        {
            memset(command, 0, sizeof(command));
            scanf("%s", command);
            if (command[0] == 'Q')
            {
                print_board();
                if (case_number > 0)
                {
                    printf("\n");
                }
                break;
            }
            else if (command[0] == 'L')
            {
                list_moves();
            }
            else if (command[0] == 'M')
            {
                int target_r = command[1] - '0' - 1;
                int target_c = command[2] - '0' - 1;
                int can_move = check_move(target_r, target_c, 0);
                if (can_move)
                {
                    // 翻转对手的棋子
                    check_move(target_r, target_c, 1);
                    board[target_r][target_c] = current_player;
                    current_player = get_opponent(current_player); // 切换玩家
                }
                else
                {
                    current_player = get_opponent(current_player); // 切换玩家
                    check_move(target_r, target_c, 1);
                    board[target_r][target_c] = current_player;
                    current_player = get_opponent(current_player); // 切换玩家
                }
                print_count();
            }
        }
    }

    return 0;
}