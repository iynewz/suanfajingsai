#include <map>
#include <cstdio>
#include <queue>
using namespace std;
const int maxt = 1000 + 5;
int main()
{
    int t, case_num = 0;
    while (scanf("%d", &t) == 1 && t != 0)
    {
        printf("Scenario #%d\n", ++case_num);
        map<int, int> team;
        for (int i = 0; i < t; i++)
        {
            int n, member;
            scanf("%d", &n);
            while (n--)
            {
                scanf("%d", &member);
                team[member] = i;
            }
        }
        queue<int> q, q2[maxt]; // q 是 team 的队列

        for (;;)
        {
            char command[10];
            int element;
            scanf("%s", command);
            if (command[0] == 'S')
            {
                break;
            }
            else if (command[0] == 'D') // DEQUEUE
            {
                int curr_team = q.front();
                printf("%d\n", q2[curr_team].front());
                q2[curr_team].pop();
                if (q2[curr_team].empty())
                {
                    q.pop();
                }
            }
            else if (command[0] == 'E') // ENQUEUE
            {
                scanf("%d", &element);
                int curr_team = team[element];
                if (q2[curr_team].empty())
                {
                    q.push(curr_team);
                };
                q2[curr_team].push(element);
            }
        }
        printf("\n");
    }
    return 0;
}