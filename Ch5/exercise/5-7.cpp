#include <iostream>
#include <queue>

using namespace std;
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        queue<pair<int, int>> q; // {priority, original index}
        priority_queue<int> pq;
        for (int i = 0; i < n; i++)
        {
            int curr_priority;
            cin >> curr_priority;
            q.push({curr_priority, i});
            pq.push(curr_priority);
        }
        int time = 0;
        int finish = 0;
        while (!q.empty())
        {
            pair<int, int> current = q.front();
            q.pop();
            if (current.first == pq.top())
            {
                pq.pop();
                time++;
                if (current.second == m)
                {
                    break; // break from while loop of line 22
                }
            }
            else // move the element to the back
            {
                q.push(current);
            }
        }
        cout << time << endl;
    }
    return 0;
}