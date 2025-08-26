// 很好的题
#include <iostream>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;
// 0 & (1 | 0) | (1 | 1 | 1 & 0)

struct Number
{
    int num;
    int op1; // 0&b 出现次数
    int op2; // 1|b 出现次数
};
stack<Number> num;
stack<char> op;
char str[1000000 + 10]; //  输入的 String 特别大，应该用 array 而不是 string 存

void calc()
{
    Number n2 = num.top();
    num.pop();
    Number n1 = num.top();
    num.pop();
    char operation = op.top();
    op.pop();
    if (n1.num == 0 && operation == '&')
    {
        num.push({0, n1.op1 + 1, n1.op2});
    }
    else if (n1.num == 1 && operation == '|')
    {
        num.push({1, n1.op1, n1.op2 + 1}); // 这里我第一次写错了，ans 是 1
    }
    else
    {
        if (operation == '&')
        {
            int ans = n1.num & n2.num;
            num.push({ans, n1.op1 + n2.op1, n1.op2 + n2.op2}); // 这里我第一次写错了，2 个都有贡献
        }
        else if (operation == '|')
        {
            int ans = n1.num | n2.num;
            num.push({ans, n1.op1 + n2.op1, n1.op2 + n2.op2});
        }
    }
}

int main()
{
    cin >> str;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '0' || str[i] == '1')
        {
            num.push({str[i] - '0', 0, 0});
        }
        else if (str[i] == '|') // 0|0|0,  0&1|0
        {
            while (!op.empty() && (op.top() == '|' || op.top() == '&')) // while!
            {
                calc();
            }
            op.push(str[i]);
        }
        else if (str[i] == '&') // 0|0&0 这种情况不需要扫描的时候先算，因为优先级 & 更高,  0&1&0
        {
            while (!op.empty() && op.top() == '&') // while! 我第一次写错了
            {
                calc();
            }
            op.push(str[i]);
        }
        else if (str[i] == '(')
        {
            op.push(str[i]);
        }
        else if (str[i] == ')')
        {
            while (!op.empty() && op.top() != '(')
            {
                calc();
            }
            op.pop(); // pop '('
        }
    }
    while (!op.empty()) // 处理剩余
    {
        calc();
    }
    // 输出
    Number ans = num.top();
    cout << ans.num << "\n"
         << ans.op1 << " " << ans.op2
         << endl;
    return 0;
}