#include <iostream>
#include <cstring>
// 出过错：病人要去的恢复室，是根据做完手术那一刻编号最小的空的恢复室决定的
// 而不是到之后编号最小的空的恢复室
// 出过错：那个the patient with the lower number指的是在门牌号小的手术室做手术的患者。那个number竟然指的门牌号！http://www.cnblogs.com/xienaoban/p/6798078.html
#include <string>
#include <queue>
using namespace std;
struct Patient
{
    string name;
    int room, b1, e1, bed, b2, e2; // 分别记录病人的手术室，手术开始时间，手术结束时间，恢复室，恢复开始时间，恢复结束时间
    int t1, t2;                    // 分别记录病人的手术和恢复时间
} pt[110];
int rm[11], bd[31]; // 记录room和bed的使用时间
struct Query
{
    int room, end, ptn;
    Query() {}
    Query(int b, int c, int d)
    {
        room = b;
        end = c;
        ptn = d;
    }
    friend bool operator<(const Query &a, const Query &b)
    {
        return (a.end > b.end) || (a.end == b.end && a.room > b.room) || (a.end == b.end && a.room == b.room && a.ptn > b.ptn);
    } // 这个排序对于病人做手术、从手术出来、恢复的排序都有效
};
int q_num = 0;
priority_queue<Query> q1;
priority_queue<Query> q2; // 记录病人从手术室出来的顺序(就是pop的顺序)、结束时间(end)、做手术的房间(room)
bool boo[31];
int n, m, T, t1, t2, t3, k, maxt;
int main()
{
    int i;
    while (scanf("%d%d%d%d%d%d%d", &n, &m, &T, &t1, &t2, &t3, &k) == 7) // 出过错：当成单组数据了
    {
        memset(boo, 0, sizeof(boo));
        memset(rm, 0, sizeof(rm));
        memset(bd, 0, sizeof(bd));
        maxt = -1;
        T = 60 * T;
        for (i = 1; i <= k; i++)
        {
            cin >> pt[i].name;
            scanf("%d%d", &pt[i].t1, &pt[i].t2);
        }
        Query qt, qt2;
        for (i = 1; i <= min(n, k); i++)
        {
            q1.push(Query(i, pt[i].t1 + T, i));
            pt[i].b1 = T;
            pt[i].room = i;
        }
        for (i = min(n, k) + 1; i <= k; i++)
        {
            qt = q1.top();
            q1.pop();
            rm[qt.room] += pt[qt.ptn].t1;
            pt[qt.ptn].e1 = qt.end;
            q1.push(Query(qt.room, qt.end + t2 + pt[i].t1, i));
            pt[i].b1 = qt.end + t2;
            pt[i].room = qt.room;
            q2.push(Query(qt.room, qt.end, qt.ptn));
        }
        while (!q1.empty())
        {
            qt = q1.top();
            q1.pop();
            rm[qt.room] += pt[qt.ptn].t1;
            pt[qt.ptn].e1 = qt.end;
            q2.push(Query(qt.room, qt.end, qt.ptn));
        }
        //	while(!q2.empty())
        //	{
        //		qt=q2.top();
        //		q2.pop();
        //		printf("%d %d %d\n",qt.end,qt.ptn,pt[qt.ptn].t2+qt.end);
        //	}
        //	for(i=1;i<=n;i++)
        //		printf("%d %d\n",i,rm[i]);
        //	for(i=1;i<=k;i++)
        //		printf("%d %d %d\n",pt[i].room,pt[i].b1,pt[i].e1);
        while (!q2.empty())
        {
            qt = q2.top();
            q2.pop();
            while (!q1.empty())
            {
                qt2 = q1.top();
                if (qt2.end + t3 <= qt.end) // 出过错：没加等号
                {
                    q1.pop();
                    pt[qt2.ptn].e2 = qt2.end;
                    boo[qt2.room] = false;
                    bd[qt2.room] += pt[qt2.ptn].t2;
                    maxt = max(maxt, qt2.end);
                }
                else
                    break;
            }
            for (i = 1; i <= m; i++)
                if (boo[i] == false)
                {
                    boo[i] = true;
                    q1.push(Query(i, qt.end + pt[qt.ptn].t2 + t1, qt.ptn));
                    pt[qt.ptn].b2 = qt.end + t1;
                    pt[qt.ptn].bed = i;
                    break;
                }
        }
        while (!q1.empty())
        {
            qt2 = q1.top();
            q1.pop();
            maxt = max(maxt, qt2.end);
            bd[qt2.room] += pt[qt2.ptn].t2;
            pt[qt2.ptn].e2 = qt2.end;
        }
        printf(" Patient          Operating Room          Recovery Room\n");
        printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
        printf(" ------------------------------------------------------\n");
        for (i = 1; i <= k; i++)
            printf("%2d  %-10s%2d   %2d:%02d   %2d:%02d     %2d   %2d:%02d   %2d:%02d\n", i, pt[i].name.c_str(), pt[i].room, pt[i].b1 / 60, pt[i].b1 % 60, pt[i].e1 / 60, pt[i].e1 % 60, pt[i].bed, pt[i].b2 / 60, pt[i].b2 % 60, pt[i].e2 / 60, pt[i].e2 % 60);
        printf("\nFacility Utilization\nType  # Minutes   Used\n");
        printf("-------------------------\n");
        maxt -= T;
        for (i = 1; i <= n; i++)
            printf("Room %2d    %4d   %5.2f\n", i, rm[i], (double)rm[i] * 100 / maxt);
        for (i = 1; i <= m; i++)
            printf("Bed  %2d    %4d   %5.2f\n", i, bd[i], (double)bd[i] * 100 / maxt);
        printf("\n"); // 注意：不要少空行
    }
    return 0;
}