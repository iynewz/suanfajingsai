#include <iostream>
#include <stack>
using namespace std;
struct Matrix
{
    int r;
    int c;
    Matrix(int r = 0, int c = 0) : r(r), c(c) {} // 构造函数
};
Matrix m[26 + 5];

int n;

void print_test()
{
    cout << "--- print matrix ---" << endl;
    for (int i = 0; i < n; i++)
    {
        char matrix_name = 'A' + i;
        cout << matrix_name << ": "
             << m[i].r << " x " << m[i].c << endl;
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char name;
        int a, b;
        cin >> name >> a >> b;
        m[name - 'A'] = Matrix(a, b);
    }
    // print_test();
    string expr;
    while (cin >> expr)
    {
        stack<Matrix> st;
        bool error = false;
        int ans = 0;

        int len = expr.length();

        for (int i = 0; i < len; i++)
        {
            char ch = expr[i];
            if (ch >= 'A' && ch <= 'Z')
            {
                st.push(m[ch - 'A']);
            }
            else if (ch == ')')
            {
                Matrix op2 = st.top();
                st.pop();
                Matrix op1 = st.top();
                st.pop();

                if (op2.r != op1.c)
                {
                    error = true;
                    break;
                }
                ans += op1.c * op1.r * op2.c;
                st.push(Matrix(op1.r, op2.c));
            }
        }
        error ? cout << "error" : cout << ans;
        cout << endl;
    }
    return 0;
}