#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;

int T;
int n; // n 个 program 并行
int c[5 + 5];
int quantum;
deque<int> readyQ; // 存 program id
queue<int> blockQ; // 存 program id
int var[26 + 5];   // 最多 26 个变量，在 n 个程序里共享
bool locked;

const int maxlinecnt = 1000; // 最多 1000 行，这是一个大致的数量
int ip[maxlinecnt];          // ip[pid]是程序 pid 的当前行号
string prog[maxlinecnt];     // 存储所有程序的指令, 从 0 开始

void execute(int pid)
{
    int q = quantum; // quantum 不变
    while (q > 0)
    {
        string command = prog[ip[pid]];
        // cout << command << endl;
        if (command[2] == '=')
        {
            char target_var = command[0];
            int target_val = isdigit(command[5]) ? (command[4] - '0') * 10 + (command[5] - '0') : (command[4] - '0');
            var[target_var - 'a'] = target_val;
            q -= c[0];
            ip[pid]++;
        }
        else if (
            command[2] == 'i' // print
        )
        {
            printf("%d: %d\n", pid + 1, var[command[6] - 'a']);
            q -= c[1];
            ip[pid]++;
        }
        else if (
            command[2] == 'c' // lock
        )
        {
            if (locked)
            {
                blockQ.push(pid);
                return; // return! 直接返回，不移动指令指针
            }
            else
            {
                locked = true;
                q -= c[2];
                ip[pid]++;
            }
        }
        else if (
            command[2] == 'l' // unlock
        )
        {
            locked = false;
            if (!blockQ.empty()) // 必须要非空检查
            {
                int pid_unlock = blockQ.front();
                blockQ.pop();
                readyQ.push_front(pid_unlock);
            }

            q -= c[3];
            ip[pid]++;
        }
        else if (
            command[2] == 'd' // end
        )
        {
            return;
        }
    }
    readyQ.push_back(pid);
}

void init()
{
    memset(var, 0, sizeof(var));
}

void test(int line)
{
    cout << "--test--" << endl;
    for (int i = 0; i < line; i++)
    {
        cout << prog[i] << endl;
    }
    return;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d %d %d %d %d %d", &n, &c[0], &c[1], &c[2], &c[3], &c[4], &quantum);
        getchar();
        init();
        int line = 0;

        for (int i = 0; i < n; i++) // n 个 program
        {
            ip[i] = line; // id 为 i
            string curr_command;

            while (getline(cin, curr_command)) // not end, continue reading
            {
                // 读取一行到string
                prog[line] = curr_command;
                line++;
                if (curr_command[2] == 'd') // end
                {
                    break;
                }
            }

            readyQ.push_back(i);
        }

        // test(line);

        locked = false;
        while (!readyQ.empty())
        {
            int pid = readyQ.front();
            readyQ.pop_front();
            execute(pid);
        }
        if (T)
        {
            printf("\n");
        }
    }
    return 0;
}