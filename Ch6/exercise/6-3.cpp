#include <iostream>
#include <vector>

using namespace std;

struct MyString
{
    const string &str_;
    int start_;
    int len_;

    MyString substr(int start, int len)
    {
        return {str_, start_ + start, len};
    }

    int find(char ch)
    {
        for (int i = start_; i < start_ + len_; i++)
        {
            if (ch == str_[start_ + len_])
            {
                return i - start_;
            }
        }
        return len_;
    }
};

void
find_post_order(string pre_order, string in_order)
{
    if (!in_order.size())
    {
        return;
    }
    char root = pre_order[0];
    int t = in_order.find(root);
    find_post_order(pre_order.substr(1, t + 1), in_order.substr(0, t));
    find_post_order(pre_order.substr(t + 1, pre_order.size()), in_order.substr(t + 1, in_order.size()));
    cout << root;
}

int main()
{
    string pre_order, in_order;
    while (cin >> pre_order >> in_order)
    {
        find_post_order(pre_order, in_order);
        cout << endl;
    }
    return 0;
}
