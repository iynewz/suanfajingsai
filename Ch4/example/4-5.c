// Spreadsheet Tracking, UVa512
// ❌ TBD: Compilation error ❌
#include<stdio.h> 
#include<string.h>
#define MAX_COMMANDS 100 // 题目里没有 n 的范围

int r, c;
int cmd_count;
int query_count;
typedef struct {
    char type[3];    // 存储 DR/DC/IR/IC/EX 命令
    int params[100]; // 存储命令作用的行号/列号/node
    int cnt;         // 记录参数个数
} Command;
Command commands[MAX_COMMANDS];
int raw_r, raw_c;
int r, c; // query node
int gone = 0;

// 降序排序辅助函数
void sort_desc(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// 删除行处理函数
void DR_command(Command cmd, int *r, int *gone_flag) {
    if (*gone_flag) return;
    sort_desc(cmd.params, cmd.cnt);
    for (int i = 0; i < cmd.cnt; i++) {
        if (cmd.params[i] == *r) {
            *gone_flag = 1;
            break;
        } else if (cmd.params[i] < *r ) {
            (*r)--;
        }
    }
}

void DC_command(Command cmd, int *c, int *gone_flag) {
    if (*gone_flag) return;
    sort_desc(cmd.params, cmd.cnt);
    for (int i = 0; i < cmd.cnt; i++) {
        if (cmd.params[i] == *c) {
            *gone_flag = 1;
            break;
        } else if (cmd.params[i] < *c) {
            (*c)--;
        }
    }
}

void IR_command(Command cmd, int *r) {
    for (int i = 0; i < cmd.cnt; i++) {
        if (cmd.params[i] <= *r) {
            (*r)++;
        }
    }
}

void IC_command(Command cmd, int *c) {
    for (int i = 0; i < cmd.cnt; i++) {
        if (cmd.params[i] <= *c) {
            (*c)++;
        }
    }
}

void EX_command(Command cmd, int *r, int *c) {
    if ((*r) == cmd.params[0] && (*c) == cmd.params[1]) {
       *r = cmd.params[2];
       *c = cmd.params[3];
    } else if ((*r) == cmd.params[2] && (*c) == cmd.params[3]) {
        *r = cmd.params[0];
        *c = cmd.params[1];
    }
}



int main() {
    while(scanf("%d%d", &r, &c) == 2 && r != 0) {
        scanf("%d", &cmd_count);
       // 保存 commands
        for (int i = 0; i < cmd_count; i++) {
            Command curr_cmd;
            curr_cmd.cnt = 0;
            scanf("%s", curr_cmd.type); // scanf %s will stop when encounter space
            // printf("curr_cmd.type:%s, i:%d\n",curr_cmd.type, i);
            while (scanf("%d", &curr_cmd.params[curr_cmd.cnt])) {
                curr_cmd.cnt++;
                if (getchar() == '\n') {
                    break;
                }
            }
            commands[i] = curr_cmd; // 第一次写漏了这一行
        }

        scanf("%d", &query_count);
        for (int i = 0; i < query_count; i++) {
            gone = 0;
            scanf("%d%d", &r, &c);
            printf("Cell data in (%d,%d) ", r, c);
            // printf("query:%d %d\n", r, c);
            // 执行 commands [] 里的每个 Command
            for (int j = 0; j < cmd_count; j++) {
                Command cmd = commands[j];
                // printf("j: %d, %c\n", j, cmd.type[0]);
                if (strcmp(cmd.type, "DR") == 0) {
                    DR_command(cmd, &r, &gone);
                } else if (strcmp(cmd.type, "DC") == 0) {
                    DC_command(cmd, &c, &gone);
                } else if (strcmp(cmd.type, "IR") == 0) {
                    IR_command(cmd, &r);
                } else if (strcmp(cmd.type, "IC") == 0) {
                    IC_command(cmd, &c);
                } else if (strcmp(cmd.type, "EX") == 0) {
                    EX_command(cmd, &r, &c);
                } 


            }
            if (gone) {
                printf("GONE\n");
            } else {
                printf("moved to (%d,%d)\n", r, c);
            }
        }
    }
    return 0;
}