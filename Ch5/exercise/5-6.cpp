#include <set>
#include <map>
#include <iostream>
using namespace std;

int main()
{
    set<pair<int, int>> dots;
    int T;
    cin >> T;
    while (T--)
    {
        dots.clear();
        int n;
        cin >> n;
        while (n--)
        {

            int x, y;
            cin >> x >> y;
            pair<int, int> x_y_pair = make_pair(x, y);
            dots.insert(x_y_pair);
        }

        int leftmost_x = dots.begin()->first;
        int rightmost_x = dots.rbegin()->first;
        double middle = (leftmost_x + rightmost_x) / 2.0;

        // cout << middle << endl;
        bool possible = true;
        auto it = dots.begin();
        while (it != dots.end())
        {
            int curr_x = (*it).first;
            if (curr_x == middle)
            {
                it = dots.erase(it); // 删除当前点，it 指向下一个元素
                continue;
            }
            int curr_y = (*it).second;
            // cout << "curr:" << curr_x << "," << curr_y << endl;
            int target_x = middle * 2 - curr_x;
            pair<int, int> target_pair = make_pair(target_x, curr_y);
            if (dots.count(target_pair))
            {
                dots.erase(target_pair);
                it = dots.erase(it); // 删除当前点，it 指向下一个元素
            }
            else
            {
                possible = false;
                break;
            }
        }
        if (dots.size() > 0)
        {
            possible = false;
        }
        possible ? cout << "YES" << endl : cout << "NO" << endl;
    }
    return 0;
}