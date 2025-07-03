#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
using namespace std;

string
generate_zero_tuple(int n)
{
    string res = "";
    while (n--)
    {
        res += "0-";
    }
    return res;
}

string calculate(const string &tuple, int n)
{
    int a[n];
    size_t start = 0;
    size_t end = tuple.find("-");
    int i = 0;
    while (end != string::npos)
    {
        a[i++] = stoi(tuple.substr(start, end - start));
        start = end + 1;
        end = tuple.find("-", start);
    }
    string new_tuple = "";

    for (int i = 0; i < n; i++)
    {
        int token;
        token = i == n - 1 ? abs(a[0] - a[i]) : abs(a[i] - a[i + 1]);
        new_tuple += (to_string(token) + "-");
    }
    return new_tuple;
}

int main()
{
    int case_num;
    cin >> case_num;
    while (case_num--)
    {
        int n;
        cin >> n;
        string tuple = "";
        map<string, int> process; // 记录新的 n 元组
        for (int i = 0; i < n; i++)
        {
            int number;
            cin >> number;
            tuple += to_string(number);
            tuple += "-"; // e.g. tuple: 8-11-2-7-
        }
        // calculate
        string zero_tuple = generate_zero_tuple(n);
        bool is_zero = false;
        while (1)
        {
            if (tuple == zero_tuple)
            {
                is_zero = true;
                break;
            }
            if (process.count(tuple))
            {
                break;
            }
            process[tuple] = 1;
            tuple = calculate(tuple, n);
        }
        is_zero ? cout << "ZERO" << endl : cout << "LOOP" << endl;
    }

    return 0;
}