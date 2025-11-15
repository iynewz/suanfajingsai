#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Token
{
    bool is_num; // true: number; false: reference
    int value;   // if is_num: number; if ref: cellID
    int sign;    // +1 or -1
};

int R, C;
vector<string> raw;
vector<vector<Token>> expr; // 解析后的 token
vector<int> state;          // 0 = 未访问, 1 = 正在访问, 2 = 已完成
vector<int> value;
vector<bool> ok; //  false = circle

int ref_to_id(const string &s)
{ // A0 -> 0
    int r = s[0] - 'A';
    int c = s[1] - '0';
    return r * C + c;
}
vector<Token> parse(const string &s)
{
    vector<Token> output;
    vector<int> signs;
    string tmp = s;

    if (tmp[0] != '-')
        signs.push_back(+1); // 补

    for (char &c : tmp)
    {
        if (c == '+')
        {
            signs.push_back(+1);
            c = ' ';
        }
        if (c == '-')
        {
            signs.push_back(-1);
            c = ' ';
        }
    }

    stringstream ss(tmp); // tmp 现在是以空格分隔的字符串
    // cout << tmp <<endl;

    string w;
    int pos = 0;
    while (ss >> w)
    {
        Token tk;
        if (isdigit(w[0]))
        {
            tk.is_num = true;
            tk.value = stoi(w);
        }
        else
        {
            tk.is_num = false;
            tk.value = ref_to_id(w); // todo
        }
        tk.sign = signs[pos++];
        output.push_back(tk);
    }

    return output;
}

int dfs(int i)
{
    if (state[i] == 2)
    {
        return value[i];
    }
    if (state[i] == 1)
    {
        ok[i] = false;
        return 0;
    } // 环

    state[i] = 1;
    int sum = 0;
    for (auto &tk : expr[i])
    {
        if (tk.is_num)
        {
            sum += tk.sign * tk.value;
        }
        else
        {
            int id = tk.value;
            int v = dfs(id);
            if (ok[id] == false)
            {
                ok[i] = false;
            }
            sum += tk.sign * v;
        }
    }
    state[i] = 2; // 完成
    value[i] = sum;
    return sum;
}

int main()
{
    while (cin >> R >> C && R && C)
    {
        int total = R * C;
        raw.resize(total);
        expr.assign(total, {});
        state.assign(total, 0);
        value.assign(total, 0);
        ok.assign(total, true);
        for (int i = 0; i < total; i++)
        {
            cin >> raw[i];
            expr[i] = parse(raw[i]);
        }
        for (int i = 0; i < total; i++)
        {
            if (state[i] == 0)
            {
                dfs(i);
            }
        }
        bool hasCircle = false;
        for (int i = 0; i < total; i++)
        {
            if (ok[i] == false)
            {
                hasCircle = true;
            }
        }
        if (!hasCircle)
        {
            cout << " ";
            for (int c = 0; c < C; c++) // header
                printf("%6d", c);
            cout << "\n";
            for (int r = 0; r < R; r++)
            {
                printf("%c", 'A' + r);
                for (int c = 0; c < C; c++)
                {
                    printf("%6d", value[r * C + c]);
                }
                cout << "\n";
            }
        }
        else
        {
            for (int i = 0; i < total; i++)
            {
                if (!ok[i])
                {
                    printf("%c%d: %s\n", 'A' + i / C, i % C, raw[i].c_str());
                }
            }
        }
        cout << "\n";
    }
    return 0;
}