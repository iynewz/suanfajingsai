#include <iostream>
#include <map>
#include <vector>
#include <stack>

using namespace std;
string s, s_left, s_right;
vector<int> array_value;

struct ArrayInfo
{
    int length;
    map<int, int> element; // <index, value>

    ArrayInfo(int length) : length(length)
    {
    }

    bool assign(int idx, int val)
    {
        if (idx >= length)
            return false;
        element[idx] = val;
        return true;
    }

    bool get_at(int idx, int &val) const
    {
        if (element.find(idx) == element.end())
        {
            return false;
        }
        val = element.find(idx)->second;
        return true;
    }
};

// struct Variables
// {
//     map<string, ArrayInfo> arrays;

//     void declare(const std::string &name, const ArrayInfo &info)
//     {
//         arrays[name] = info;
//     }

//     void get_value()
// }

// void test_array()
// {
//     ArrayInfo arr(30);
//     assert(arr.assign(0, 10));
//     assert(!arr.assign(30, 10));

//     int val = -1;
//     assert(arr.get_at(0, val));
//     assert(val == 10);

//     assert(!arr.get_at(1, val));
//     assert(!arr.get_at(31, val));
// }

pair<string, string> split_name_index(const string &s)
{
    int left_bracket_pos = s.find('[');
    int right_bracket_pos = s.rfind(']');
    string array_name = s.substr(0, left_bracket_pos);
    string index = s.substr(left_bracket_pos + 1, right_bracket_pos - left_bracket_pos - 1);
    return {array_name, index};
}

// void test_split_name_index()
// {
//     pair<string, string> res = split_name_index("a[1]");
//     assert(res.first == "a");
//     assert(res.second == "1");

//     res = split_name_index("a[b[c[d[1]]]]");
//     assert(res.first == "a");
//     assert(res.second == "b[c[d[1]]]");
// }

// a[10];
// a[1] = 0;

// expr = a[b[c[10]]]
// res = {a, eval(b[c[10]])}
bool eval(const map<string, ArrayInfo> &arrays, const string &expr, pair<string, int> &res)
{
    pair<string, string> kv = split_name_index(expr);
    if (kv.second.find('[') == -1)
    {
        res.first = kv.first;
        res.second = stoi(kv.second);
        return true;
    }
    else
    {
        eval(arrays, kv.second, res);
        if (!arrays.find(res.first)->second.get_at(res.second, res.second))
        {
            return false;
        }
        res.first = kv.first;
        return true;
    }
}

/*
bool parse_name_index2(const string &s, const map<string, ArrayInfo> &arrays, pair<string, int> &res) // parse a[a[a[1]]] ->  {a, 6} if a[a[1]] == 6
{
    stack<int> bracket_stack; // 记录括号位置
    string array_name = split_name_index(s).first;
    int len = s.size();
    int final_index = -1;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '[')
        {

            bracket_stack.push(i);
        }
        else if (s[i] == ']' && !bracket_stack.empty())
        {
            int left_pos = bracket_stack.top();
            bracket_stack.pop();
            string index_str = s.substr(left_pos + 1, i - left_pos - 1);
            int index = stoi(index_str); // 将索引部分转换为整数
            if (final_index == -1)
            {
                final_index = index;
            }
            else
            {
                final_index = get_array_value(array_name, final_index, arrays, found_bug);
            }
        }
    }
    return {array_name, final_index};
}
    */

int main()
{
    bool case_over = false; // 判断是否结束读取测试用例

    while (!case_over)
    {
        case_over = true;
        int line = 0;
        bool found_bug = false;

        map<string, ArrayInfo> arrays;

        while (cin >> s && s[0] != '.')
        {
            if (found_bug)
            {
                continue;
            }
            case_over = false;
            line++;
            int equal_pos = s.find('=');
            if (equal_pos == -1) // 声明语句 declaration
            {
                pair<string, string> parsed_pair = split_name_index(s);
                ArrayInfo curr_array(stoi(parsed_pair.second));
                arrays.emplace(parsed_pair.first, curr_array);
            }
            else // 赋值语句 expression
            {
                s_left = s.substr(0, equal_pos);
                s_right = s.substr(equal_pos + 1);
                int value;

                if (s_right.find('[') == -1) // 立即数
                {
                    value = stoi(s_right);
                }
                else
                {
                    pair<string, int> res;
                    if (!eval(arrays, s_right, res))
                    {
                        found_bug = true;
                        continue;
                    }
                    if (!arrays.find(res.first)->second.get_at(res.second, value))
                    {
                        found_bug = true;
                    }
                }

                pair<string, int> res;
                if (!eval(arrays, s_left, res))
                {
                    found_bug = true;
                    continue;
                }
                if (!arrays.find(res.first)->second.assign(res.second, value))
                {
                    found_bug = true;
                }
            }
        }

        if (case_over) {
            break;
        }

        found_bug ? cout << line << endl : cout << 0 << endl;
    }
    return 0;
}
