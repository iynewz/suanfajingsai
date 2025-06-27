#include <iostream>
#include <vector>
#include <sstream>
#include <climits>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstring>

#define rep(i, x, y) for (int i = (x); i <= (y); i++)
using namespace std;
typedef long double lf;
const int maxPz = 77, maxP = 150;
lf prize[maxPz];
struct player

{
    string name;
    int score[5], dqpos, tot, rnk;
    bool isamateur, tie;
} p[maxP];
int tienum[maxP];

void debug(int num)
{
    rep(i, 1, num)
    {
        cout << p[i].name << " ";
        rep(j, 1, 4)
            printf("%d ", p[i].score[j]);
        printf("%d %d\n", p[i].dqpos, p[i].isamateur);
    }
}

struct cmp1
{
    bool operator()(const player &a, const player &b)
    {
        return a.score[1] + a.score[2] < b.score[1] + b.score[2];
    }
};
struct cmp2
{
    bool operator()(const player &a, const player &b)
    {
        if (a.dqpos < 5 && b.dqpos < 5)
        {
            if (a.dqpos != b.dqpos)
                return a.dqpos > b.dqpos;
            if (a.tot != b.tot)
                return a.tot < b.tot;
            return a.name < b.name;
        }
        if (a.dqpos < 5)
            return false;
        if (b.dqpos < 5)
            return true;
        if (a.tot != b.tot)
            return a.tot < b.tot;
        return a.name < b.name;
    }
};

int main()
{
    int T;
    cin >> T;
    bool isfirst = true;
    while (T--)
    {
        if (isfirst)
            isfirst = false;
        else
            cout << "\n";
        lf tot;
        cin >> tot;
        rep(i, 1, 70)
        {
            lf perc;
            cin >> perc;
            prize[i] = tot * perc / 100.0;
        }
        int num;
        cin >> num;
        string s;
        getline(cin, s);
        rep(i, 1, num)
        {
            getline(cin, s);
            p[i].name = s.substr(0, 20);
            p[i].isamateur = false;
            rep(j, 0, 19) if (p[i].name[j] == '*')
                p[i]
                    .isamateur = true;
            p[i].dqpos = 5;
            rep(j, 1, 4) if (s[17 + j * 3] == 'D' || s[18 + j * 3] == 'D')
            {
                p[i].dqpos = j;
                break;
            }
            else sscanf(s.substr(17 + j * 3, 3).c_str(), "%d", p[i].score + j);
        }
        {
            int j = 1;
            rep(i, 1, num) if (!(p[i].dqpos <= 2))
                swap(p[i], p[j++]);
            num = j - 1;
        }
        {
            rep(i, 1, num) if (p[i].dqpos == 5)
                p[i]
                    .tot = p[i].score[1] + p[i].score[2] + p[i].score[3] + p[i].score[4];
            else
            {
                p[i].tot = 0;
                rep(j, 1, p[i].dqpos - 1)
                    p[i]
                        .tot += p[i].score[j];
            }
        }
        sort(p + 1, p + num + 1, cmp1());
        {
            rep(i, 70, num - 1) if (p[i].score[1] + p[i].score[2] != p[i + 1].score[1] + p[i + 1].score[2])
            {
                num = i;
                break;
            }
        }
        sort(p + 1, p + num + 1, cmp2());
        printf(
            "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n"
            "-----------------------------------------------------------------------\n");
        {
            int tie_first = 1, tie_rank = 1;
            rep(i, 1, num)
            {
                p[i].tie = false;
                if (i > 1 && p[i].tot == p[tie_first].tot)
                    p[i].tie = true;
                else
                {
                    tie_first = i, tie_rank = i;
                    if (i < num && p[i].tot == p[i + 1].tot)
                        p[i].tie = true;
                }
                p[i].rnk = tie_rank;
                if (p[i].tie && !p[i].isamateur)
                    tienum[p[i].rnk]++;
            }
        }
        {
            int przrnk = 1, przfst = 1;
            rep(i, 1, num)
            {
                cout << p[i].name << " ";
                if (p[i].tot != p[i - 1].tot)
                    przfst = przrnk;
                if (p[i].dqpos == 5)
                {
                    if (tienum[p[i].rnk] > 1 && !p[i].isamateur && przfst <= 70)
                    {
                        char tmp[20];
                        memset(tmp, 0, sizeof(tmp));
                        sprintf(tmp, "%dT", p[i].rnk);
                        printf("%-10s", tmp);
                    }
                    else
                        printf("%-10d", p[i].rnk);
                }
                else
                    printf("          ");
                rep(j, 1, 4) if (p[i].dqpos > j)
                    printf("%-5d", p[i].score[j]);
                else printf("     ");
                if (p[i].dqpos == 5 && !p[i].isamateur && przfst <= 70)
                {
                    if (p[i].dqpos != 5)
                        printf("DQ        ");
                    else
                        printf("%-10d", p[i].tot);
                }
                else
                {
                    if (p[i].dqpos != 5)
                        printf("DQ");
                    else
                        printf("%d", p[i].tot);
                }
                if (p[i].dqpos == 5 && !p[i].isamateur && przfst <= 70)
                {
                    if (!p[i].tie)
                        printf("$%9.2Lf", prize[przrnk]);
                    else
                    {
                        lf totpz = 0;
                        rep(j, przfst, przfst + tienum[p[i].rnk] - 1)
                            totpz += prize[j];
                        printf("$%9.2Lf", totpz / tienum[p[i].rnk]);
                    }
                    przrnk++;
                }
                printf("\n");
            }
        }
        memset(tienum, 0, sizeof(tienum));
    }
    return 0;
}