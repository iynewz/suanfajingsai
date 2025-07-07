#include <queue>
#include <iostream>

using namespace std;
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        queue<int> q;
        for (int i = 1; i <= n; i++)
        {
            q.push(i);
        }
        int initial_size = q.size();
        cout << "Discarded cards:";
        while (q.size() > 1)
        {
            int throw_away = q.front();
            q.pop();
            bool is_first_pop = q.size() == initial_size - 1;
            !is_first_pop &&cout << ",";
            cout << " " << throw_away;
            int next = q.front();
            q.pop();
            q.push(next);
        }
        cout << endl;
        cout << "Remaining card: " << q.front() << endl;
    }
    return 0;
}