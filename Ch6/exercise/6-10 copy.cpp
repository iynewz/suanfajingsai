//WA
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

int cnt;

class CardsState
{
public:
    vector<vector<int>> cards; // 0: hand; 1-7: piles

    bool win() { return cards[0].size() == 52; }
    bool lose() { return cards[0].size() == 0; }

    bool operator<(const CardsState &rhs) const
    {
        if (cards.size() != rhs.cards.size())
            return cards.size() < rhs.cards.size();
        for (size_t i = 0; i < cards.size(); i++)
        {
            if (cards[i].size() != rhs.cards[i].size())
                return cards[i].size() < rhs.cards[i].size();
            for (size_t j = 0; j < cards[i].size(); j++)
            {
                if (cards[i][j] != rhs.cards[i][j])
                    return cards[i][j] < rhs.cards[i][j];
            }
        }
        return false;
    }

    CardsState(int first_card)
    {
        cards.resize(8);
        cards[1].push_back(first_card);
        for (int i = 2; i <= 7; i++)
        {
            int card;
            cin >> card;
            cards[i].push_back(card);
        }
        for (int i = 1; i <= 7; i++)
        {
            int card;
            cin >> card;
            cards[i].push_back(card);
        }
        for (int i = 7 * 2 + 1; i <= 52; i++)
        {
            int card;
            cin >> card;
            cards[0].push_back(card);
        }
        cnt += 14;
    }

    void reduce(int curr)
    {
        while (cards[curr].size() >= 3)
        {
            int n = cards[curr].size();

            if ((cards[curr][0] + cards[curr][1] + cards[curr][n - 1]) % 10 == 0)
            {
                cards[0].push_back(cards[curr][0]);
                cards[0].push_back(cards[curr][1]);
                cards[0].push_back(cards[curr][n - 1]);
                cards[curr].erase(cards[curr].begin() + (n - 1));
                cards[curr].erase(cards[curr].begin());
                cards[curr].erase(cards[curr].begin());
            }
            else if ((cards[curr][0] + cards[curr][n - 2] + cards[curr][n - 1]) % 10 == 0)
            {
                cards[0].push_back(cards[curr][0]);
                cards[0].push_back(cards[curr][n - 2]);
                cards[0].push_back(cards[curr][n - 1]);
                cards[curr].erase(cards[curr].begin() + (n - 1));
                cards[curr].erase(cards[curr].begin() + (n - 2));
                cards[curr].erase(cards[curr].begin());
            }
            else if ((cards[curr][n - 3] + cards[curr][n - 2] + cards[curr][n - 1]) % 10 == 0)
            {
                cards[0].push_back(cards[curr][n - 3]);
                cards[0].push_back(cards[curr][n - 2]);
                cards[0].push_back(cards[curr][n - 1]);
                cards[curr].erase(cards[curr].begin() + (n - 1));
                cards[curr].erase(cards[curr].begin() + (n - 2));
                cards[curr].erase(cards[curr].begin() + (n - 3));
            }
            else
            {
                break;
            }
        }
    }

    void next(set<CardsState> &records)
    {
        int cur_pile = 1; // [1, 7] piles
        while (!cards[0].empty() && cur_pile <= 7)
        {
            bool duplicate = records.find(*this) != records.end();

            if (win() || lose() || duplicate)
            {
                if (duplicate)
                {
                    cout << "Draw: " << cnt << endl;
                }
                else if (win())
                {
                    cout << "Win : " << cnt << endl;
                }
                if (lose())
                {
                    cout << "Loss: " << cnt << endl;
                }
                return;
            }
            records.insert(*this);

            if (cards[cur_pile].empty())
            {
                cur_pile++;
                continue;
            }

            cards[cur_pile].push_back(cards[0][0]);
            cards[0].erase(cards[0].begin());
            cnt++;

            reduce(cur_pile);
            cur_pile++;
        }
    }
};

int main()
{
    int tmp;
    while (cin >> tmp)
    {
        if (tmp == 0)
            break;

        cnt = 0;
        CardsState state(tmp);
        set<CardsState> records;

        while (true)
        {
            state.next(records);
        }
    }

    return 0;
}
