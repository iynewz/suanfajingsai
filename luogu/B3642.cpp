#include <iostream>
using namespace std;

struct BinaryTree
{
    int leftChild, rightChild;
};
BinaryTree tree[100000];

void preOrder(int i) // 根 左 右
{
    cout << i << " ";
    if (tree[i].leftChild)
    {
        preOrder(tree[i].leftChild);
    }
    if (tree[i].rightChild)
    {
        preOrder(tree[i].rightChild);
    }
}

void inOrder(int i) //  左 根 右
{
    if (tree[i].leftChild)
    {
        inOrder(tree[i].leftChild);
    }
    cout << i << " ";
    if (tree[i].rightChild)
    {
        inOrder(tree[i].rightChild);
    }
}

void postOrder(int i) //  左 右 根
{
    if (tree[i].leftChild)
    {
        postOrder(tree[i].leftChild);
    }
    if (tree[i].rightChild)
    {
        postOrder(tree[i].rightChild);
    }
    cout << i << " ";
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        BinaryTree temp;
        cin >> temp.leftChild >> temp.rightChild;
        tree[i] = temp;
    }
    preOrder(1);
    cout << endl;
    inOrder(1);
    cout << endl;
    postOrder(1);
    cout << endl;
    return 0;
}