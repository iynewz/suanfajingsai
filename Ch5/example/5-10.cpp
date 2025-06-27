#include <iostream>
#include <vector>
#include <sstream>
#include <climits>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

const int purse_count = 70;
const string HEADER = "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n-----------------------------------------------------------------------";
const string amateur_flag = "*";
struct Player
{
    string name;
    bool amateur;
    int score[4];
    int DQ_position;
    int ho36;
    int ho72;
    string total;
    string place; // 名次（如 "2T", "3" 等）
    double money; //
    int rounds_completed() const
    {
        if (DQ_position >= 0)
            return DQ_position;
        else
            return 4;
    }
};

double purse_total;
double purse[purse_count + 5];
int player_count;
vector<Player> players;

bool check_contain_amateur(const string &s)
{
    return (s.find(amateur_flag) != string::npos);
}

bool comparePlayers_36(const Player &a, const Player &b)
{
    return a.ho36 < b.ho36;
}

bool comparePlayers_72(const Player &a, const Player &b)
{
    int rounds_a = a.rounds_completed();
    int rounds_b = b.rounds_completed();
    if (a.ho72 != b.ho72 && rounds_a == 4 && rounds_b == 4)
        return a.ho72 < b.ho72;
    if (rounds_a != 4 || rounds_b != 4)
    {
        if (rounds_a != rounds_b)
            return rounds_a > rounds_b;
        if (a.ho72 != b.ho72)
            return a.ho72 < b.ho72;
    }
    return a.name < b.name;
}

bool isComplete(const Player &p)
{
    return (p.rounds_completed() == 4);
}

void assignMoney(vector<Player> &players)
{
    int purse_index = 0; // 当前分配的奖金比例索引
    int i = 0;           // 当前处理的选手索引

    while (i < players.size() && purse_index < purse_count)
    {
        // 跳过未完成比赛的选手
        if (players[i].rounds_completed() < 4)
        {
            players[i].money = -1;
            i++;
            continue;
        }

        // 分组：找出所有并列的选手
        int j = i;
        int pro_count = 0;             // 组内非业余选手数量
        double group_percentage = 0.0; // 组内可分配的奖金比例总和

        // 找出所有总分相同的选手
        while (j < players.size() && players[j].ho72 == players[i].ho72 &&
               players[j].rounds_completed() == 4)
        {
            // 统计非业余选手数量
            if (!players[j].amateur)
            {
                pro_count++;
                // 如果有奖金比例可用，则累加
                if (purse_index < purse_count)
                {
                    group_percentage += purse[purse_index];
                    purse_index++;
                }
            }
            j++;
        }

        // 计算每个非业余选手的奖金
        double money_per_pro = 0.0;
        // bool has_money = (group_percentage > 0); // 该组是否有奖金分配

        if (pro_count > 0)
        {
            money_per_pro = (group_percentage * purse_total) / 100.0 / pro_count;
            // 四舍五入到两位小数
            money_per_pro = round(money_per_pro * 100.0) / 100.0; // todo： no round
        }

        // 分配奖金给组内非业余选手
        for (int k = i; k < j; k++)
        {
            players[k].money = players[k].amateur ? -1 : money_per_pro;
        }
        i = j; // 移动到下一组
    }

    // 处理奖金已分配完毕的情况
    while (i < players.size())
    {
        // 所有剩余选手（包括非业余选手）都无法获得奖金
        players[i].money = -1;
        i++;
    }
}

void assignPlaces(vector<Player> &players)
{
    int current_rank = 1;
    size_t i = 0;

    while (i < players.size())
    {
        if (players[i].rounds_completed() < 4)
        {
            players[i].place = "";
            players[i].total = "DQ";
            i++;
            continue;
        }

        // 找出当前分数段的所有选手
        double current_score = players[i].ho72;
        size_t j = i;
        vector<size_t> group;      // 存储同分组选手索引
        int proWithMoneyCount = 0; // 统计非业余奖金选手数量

        // 收集同分选手并统计符合条件的职业选手
        while (j < players.size() && players[j].ho72 == current_score)
        {
            if (players[j].rounds_completed() < 4)
                break;

            group.push_back(j);

            // 统计非业余且获得奖金的选手
            if (!players[j].amateur && players[j].money != -1)
            {
                proWithMoneyCount++;
            }
            j++;
        }

        // 确定组内是否需要添加T标记
        bool addTieSuffix = (proWithMoneyCount >= 2);
        int group_size = group.size();

        // 处理组内每个选手
        for (size_t k = 0; k < group.size(); ++k)
        {
            size_t idx = group[k];
            if (addTieSuffix && !players[idx].amateur && players[idx].money != -1)
            {
                players[idx].place = to_string(current_rank) + 'T';
            }
            else
            {
                players[idx].place = to_string(current_rank);
            }
            players[idx].total = players[idx].ho72; // 确保设置总杆数
        }

        // 更新名次（跳过当前组占用的所有名次）
        current_rank += group_size;
        i = j; // 移动到下一组
    }
}

int main()
{
    int case_num;
    cin >> case_num;
    for (int i = 0; i < case_num; i++)
    {
        cin.ignore(); // 忽略换行符
        cin >> purse_total;
        for (int k = 0; k < purse_count; k++)
        {
            cin >> purse[k];
        }
        cin >> player_count;
        cin.ignore(); // 忽略 player_count后的换行符
        players.clear();
        for (int p = 0; p < player_count; p++)
        {
            int round_0_1 = 0;
            int round_2_3 = 0;
            Player curr_p;
            string s;
            getline(cin, s);

            // 提取名字
            if (s.length() >= 20)
            {
                curr_p.name = s.substr(0, 20);
            }
            else
            {
                // 如果行长度不足20，就用整个字符串作为名字，并用空格补齐
                curr_p.name = s;
                curr_p.name.resize(20, ' ');
            }

            curr_p.amateur = check_contain_amateur(curr_p.name);
            curr_p.DQ_position = -1;

            // 提取分数
            string scores_str;
            if (s.length() > 21)
            {
                scores_str = s.substr(21);
            }
            else
            {
                scores_str = ""; // 如果长度不足，说明没有分数，scores_str 为空
            }

            stringstream ss(scores_str);
            for (int j = 0; j < 4; j++)
            {
                string token;
                if (ss >> token)
                {
                    if (token == "DQ")
                    {
                        curr_p.DQ_position = j;
                        curr_p.score[j] = -1; // DQ
                    }
                    else
                    {
                        int round_score = stoi(token);
                        curr_p.score[j] = round_score;
                        j <= 1 ? (round_0_1 += round_score) : (round_2_3 += round_score);
                    }
                }
                else
                {
                    curr_p.score[j] = -1; // DQ 之后没有成绩
                }
            }

            curr_p.ho36 = round_0_1;
            curr_p.ho72 = round_0_1 + round_2_3;
            if (curr_p.DQ_position == -1 || curr_p.DQ_position > 1)
            {
                players.push_back(curr_p); // 如果在前 2 轮违规，一定不能晋级
            }
        }

        sort(players.begin(), players.end(), comparePlayers_36);

        vector<Player> qualified_players;
        int cut_off_score = players[purse_count - 1].ho36;
        int qualified_count = purse_count;
        while (qualified_count < players.size() && players[qualified_count].ho36 == cut_off_score)
        {
            qualified_count++; // 得到包含并列的总晋级人数
        }

        if (qualified_count < players.size()) // 题目虽然保证了晋级人数 at lease 70，但有的数据集会人数不够。
        {
            players.erase(players.begin() + qualified_count, players.end());
        }

        sort(players.begin(), players.end(), comparePlayers_72);
        // 未完成的排在后面
        vector<Player>::iterator complete_end =
            partition(players.begin(), players.end(), isComplete);

        assignMoney(players);

        assignPlaces(players);

        i != 0 && cout << endl;
        cout << HEADER << endl;
        for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {

            cout << left << setw(21) << it->name << setw(10) << it->place;
            for (int score_index = 0; score_index < 4; score_index++)
            {
                it->score[score_index] == -1 ? cout << setw(5) << " " : cout << setw(5) << it->score[score_index];
            }
            (it->total == "DQ") ? cout << it->total : (it->money == -1) ? cout << it->ho72
                                                                        : cout << setw(10) << it->ho72;
            // cout << it->money << endl;
            (it->money == -1) ? cout << endl : cout << "$" << right << setw(9) << fixed << setprecision(2) << it->money << endl;
        }
    }
    return 0;
}