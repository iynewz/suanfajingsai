#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int w; // 子树总重量
    Node *left;
    Node *right;

    Node(int w) : w(w), left(NULL), right(NULL) {}
    Node(Node *L, Node *R) : left(L), right(R)
    {
        w = L->w + R->w;
    }
};

vector<Node *> nodes;
int kase;
double r;
int n;
vector<int> w; // 挂坠重量
bool possible;

void printTree(Node *node, int depth = 0)
{
    if (!node)
        return;
    for (int i = 0; i < depth; i++)
        cout << "  "; // 缩进表示深度
    cout << "Node weight: " << node->w << endl;
    printTree(node->left, depth + 1);
    printTree(node->right, depth + 1);
}

void dfs(vector<Node *> &cur)
{
    // 结束条件：只剩一个节点，就是一棵完整的二叉树
    if (cur.size() == 1)
    {
        Node *root = cur[0];
        // test
        cout << "Tree structure:\n";
        printTree(root);
        cout << "Root total weight: " << root->w << "\n\n";
        return;
    }

    for (int i = 0; i < cur.size(); i++)
    {
        for (int j = i + 1; j < cur.size(); j++)
        {

            Node *a = cur[i];
            Node *b = cur[j];

            Node *t1 = new Node(cur[i], cur[j]);

            // 构造下一层的节点集合
            vector<Node *> nxt;
            for (int k = 0; k < cur.size(); k++)
            {
                if (k != i && k != j)
                    nxt.push_back(cur[k]);
            }
            nxt.push_back(t1);

            dfs(nxt);

            // 这里不用手动 delete
        }
    }
}

int main()
{
    cin >> kase;
    while (kase--)
    {
        cin >> r >> n;
        w.resize(n);

        vector<Node *> init;
        for (int i = 0; i < n; i++)
        {
            cin >> w[i];
            init.push_back(new Node(w[i]));
        }

        dfs(init);
    }
}
