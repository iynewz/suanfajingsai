#include <iostream>
using namespace std;

struct BinaryTree
{
    int right, left;
    int val;
};

BinaryTree BST[300005];
int N, Depth;

int buildBST(int curr, int i, int depth)
// curr: 当前节点编号， i: 需要放置的节点编号，depth: 树的当前深度
{
    if (curr == 0)
    {
        Depth = max(depth, Depth);
        return i;
    }
    if (BST[i].val > BST[curr].val)
    { // 放在右子树
        BST[curr].right = buildBST(BST[curr].right, i, depth + 1);
    }
    else
    {
        BST[curr].left = buildBST(BST[curr].left, i, depth + 1);
    }
    return curr;
}

void postOrder(int i)
{ // 左，右，根
    if (i == 0)
    {
        return;
    }
    postOrder(BST[i].left);
    postOrder(BST[i].right);
    cout << BST[i].val << endl;
}
int main()
{
    cin >> N;
    int val;
    cin >> BST[1].val;
    Depth = 1;
    for (int i = 2; i <= N; i++)
    {
        cin >> BST[i].val;
        buildBST(1, i, 1);
    }
    cout << "deep=" << Depth << endl;
    postOrder(1);
    return 0;
}