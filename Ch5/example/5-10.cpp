#include <iostream>
#include <vector>
#include <sstream>
#include <climits>
#include <string>
#include <iomanip>

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
    string place;        // 名次（如 "2T", "3" 等）
    double money;        //
    string money_string; // $  7245.28
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
    if (a.ho72 != b.ho72)
        return a.ho72 < b.ho72;
    int rounds_a = a.rounds_completed();
    int rounds_b = b.rounds_completed();
    if (rounds_a != rounds_b)
        return rounds_a > rounds_b;
    return a.name < b.name;
}

bool isComplete(const Player &p)
{
    return (p.rounds_completed() == 4);
}

void assignMoney(vector<Player> &players)
{
    for (size_t i = 0; i < players.size(); ++i)
    {
        players[i].money = 100; // hardcode
    }
}
void assignPlaces(vector<Player> &players)
{
    int current_rank = 1;
    for (size_t i = 0; i < players.size(); ++i)
    {
        if (players[i].rounds_completed() < 4)
        {
            players[i].place = "";
            players[i].total = "DQ";
            continue;
        }
        else
        {
            players[i].total = players[i].ho72;
        }

        // 检查是否需要处理并列
        bool is_tie = (i > 0 && players[i].ho72 == players[i - 1].ho72);

        if (is_tie)
        {
            // 只有当前选手和前一个选手都是非业余且都获得奖金时，才加 'T'
            if (!players[i].amateur && players[i].money > 0 &&
                !players[i - 1].amateur && players[i - 1].money > 0)
            {
                // 如果前一个选手的名次没有 'T'，则添加
                if (players[i - 1].place.find('T') == string::npos)
                {
                    players[i - 1].place += "T";
                }
                players[i].place = players[i - 1].place;
            }
            else
            {
                players[i].place = players[i - 1].place;
            }
            current_rank++;
        }
        else
        {
            players[i].place = to_string(current_rank);
            current_rank++;
        }
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
            if (0 <= curr_p.DQ_position && curr_p.DQ_position <= 1)
            {
                curr_p.ho36 = INT_MAX; // 如果在前 2 轮违规，一定不能晋级
            }
            players.push_back(curr_p);
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

        // 晋级后，先按是否完成分组（未完成的排在后面）
        vector<Player>::iterator complete_end =
            partition(players.begin(), players.end(), isComplete);

        // 对已完成的部分排序
        sort(players.begin(), complete_end, comparePlayers_72);

        // 处理每个 player 的奖金
        assignMoney(players); // todo

        // 处理 Place 次序
        assignPlaces(players);

        // print
        cout
            << HEADER << endl;
        // print players for test
        for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {

            cout << left << setw(21) << it->name << setw(10) << it->place << setw(5) << it->score[0] << setw(5) << it->score[1] << setw(5) << it->score[2] << setw(5) << it->score[3] << setw(10) << it->ho72 << setw(3) << "$" << endl;
        }
        cout << endl;
    }
    return 0;
}