#include <iostream>
using namespace std;
string inOrder, postOrder;

void findPreOrder(string inOrder, string postOrder)
{
    if (!inOrder.size())
    {
        return;
    }
    char root = postOrder[postOrder.size() - 1];
    cout << root;
    int t = inOrder.find(root);

    findPreOrder(inOrder.substr(0, t), postOrder.substr(0, t));
    findPreOrder(inOrder.substr(t + 1), postOrder.substr(t, postOrder.size() - t - 1));
}
int main()
{
    cin >> inOrder >> postOrder;
    findPreOrder(inOrder, postOrder);
    cout << endl;
    return 0;
}