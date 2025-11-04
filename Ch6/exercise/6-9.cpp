#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
vector<stack<string>> cards;
vector<stack<string>> cards_2;

bool can_match(const string &a, const string &b)
{
    return (a[0] == b[0] || a[1] == b[1]);
};
void check_cards()
{
    int len = cards.size();
    for (int i = 0; i < len; i++)
    {
        string curr_top = cards[i].top();
        if (i - 3 >= 0 && can_match(curr_top, cards[i - 3].top()))
        {
            cards[i - 3].push(curr_top);
            cards[i].pop();
            if (cards[i].empty())
            {
                cards.erase(cards.begin() + i);
            }
            check_cards();
            return;
        }
        else if (i - 1 >= 0 && can_match(curr_top, cards[i - 1].top()))
        {
            cards[i - 1].push(curr_top);
            cards[i].pop();
            if (cards[i].empty())
            {
                cards.erase(cards.begin() + i);
            }
            check_cards();
            return;
        }
    }
}

int main()
{
    string tmp;
    while (true)
    {
        cards.clear();
        cards.assign(52, stack<string>());
        cin >> tmp;
        if (tmp == "#")
            break;

        cards[0].push(tmp);

        for (int i = 1; i < 52; i++)
        {
            cin >> tmp;
            cards[i].push(tmp);
        }

        check_cards();
        int size = cards.size();

        cout << size << " pile";
        cout << ((size == 1) ? "" : "s");
        cout << " remaining:";
        for (auto &c : cards)
            cout << " " << c.size();
        cout << endl;
    }

    return 0;
}
