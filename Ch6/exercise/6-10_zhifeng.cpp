// wrong answer

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Game;

class CardsState
{
public:
    vector<vector<int>> cards; // 0: hand; 1-7: piles
    Game *game;
    int cnt;

    bool win()
    {
        return cards[0].size() == 52;
    }

    bool lose()
    {
        return cards[0].size() == 0;
    }

    bool operator<(const CardsState &rhs) const
    {
        int len = cards.size();
        int len_rhs = rhs.cards.size();
        if (len != len_rhs) //
        {
            return len < len_rhs;
        }
        for (int i = 0; i < len; i++)
        {
            int len_2 = cards[i].size();
            int len_2_rhs = rhs.cards[i].size();
            if (len_2 != len_2_rhs)
            {
                return len_2 < len_2_rhs;
            }
            for (int j = 0; j < len_2; j++)
            {
                if (cards[i][j] != rhs.cards[i][j])
                {
                    return cards[i][j] < rhs.cards[i][j];
                }
            }
        }
        return false;
    }

    CardsState(int first_card, Game* game): game(game), cnt(0)
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

    bool next();

    bool terminate();
};

class Game
{
public:
    set<CardsState> records;

    bool duplicate(CardsState* state)
    {
        if (records.find(*state) == records.end()) {
            new_state(state);
            return false;
        }
        return true;
    }

    void new_state(CardsState*state) {
        records.insert(*state);
    }
};

bool CardsState::terminate() {
        std::string finished;

        if (win())
        {
            finished = "Win : ";
        }
        if (lose())
        {
            finished = "Loss: ";
        }
        if (game->duplicate(this))
        {
            finished = "Draw: ";
        }
        if (finished.length() > 0) {
            cout << finished << cnt << endl;
            return true;
        }
        return false;
    }

bool CardsState::next()
{
    int cur_pile = 1; // [1, 7] piles
    while (cards[0].size() > 0 && cur_pile <= 7)
    {
        if (cards[cur_pile].size() == 0)
        {
            cur_pile++;
            continue;
        }

        
        cards[cur_pile].push_back(cards[0][0]);
        cards[0].erase(cards[0].begin());
        cnt++;
        reduce(cur_pile);
        if (terminate()) {
            return false;
        }

        cur_pile++;
    }
    return true;
}

int main()
{
    int tmp;
    while (true)
    {
        cin >> tmp;
        if (tmp == 0)
        {
            break;
        }
        else
        {
            Game game;
            CardsState state(tmp, &game);
            while (state.next()) {
                if (state.terminate()) {
                    break;
                }
            }
        }
    }
    return 0;
}