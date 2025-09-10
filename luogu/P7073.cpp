#include <iostream>
using namespace std;

// x1 ! x2 x4 | x3 x5 ! & & ! &
// 5
// 0 1 0 1 1
// 3
// 1
// 3
// 5
const int N = 1000000;
struct Node
{
    bool type; // true - 变量 x; false - operators
    int data;  // 变量 x 的下标
};
Node nodes[N];
int cnt;

struct TreeNode
{
    int l, r;
    bool type;
    int data;
};
TreeNode tree[2 * N];
int root;
int w[N], x[N];

bool isOp(char c)
{
    if (c == '|' || c == '&' || c == '!')
    {
        return true;
    }
    return false;
}

void parse_string(string s)
{
    int len = s.size();
    bool type = true;
    int data;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == 'x')
        {
            type = true;
            data = 0;
        }
        else if (isdigit(s[i]))
        {
            data = data * 10 + s[i] - '0';
        }
        else if (isOp(s[i]))
        {
            type = false;
            data = s[i];
        }
        else // space
        {
            nodes[++cnt].type = type;
            nodes[cnt].data = data;
        }
    }
}
void test_print_nodes()
{
    for (int i = 1; i <= cnt; i++)
    {
        cout << nodes[i].data << " ";
    }
}

int k = 0;
void build_tree()
{
    stack<int> st; // why inside?
    for (int i = 1; i <= cnt; i++)
    {
        k++;
        if (nodes[i].type)
        {
            tree[k].l = 0;
            tree[k].r = 0;
            tree[k].type = true;
            tree[k].data = nodes[i].data;
            w[k] = x[nodes[i].data];
            st.push(k);
        }
        else
        {
        }
    }
}
int main()
{
    string s;
    getline(cin, s);
    parse_string(s);
    // test_print_nodes();
    build_tree();
    return 0;
}


yaxin@ccf.org.cn
//6.30

