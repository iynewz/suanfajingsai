#include <map>
#include <string>
using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) == 1 && n != 0)
    {
        map<string, int> school;
        while (n--)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            string key = to_string(a) + '-' + to_string(b);
            school[key]++;
        }
        bool possible = true;
        if (n % 2 == 1)
        {
            possible = false;
            continue;
        }
        // 判断是否可以配对

        for (map<string, int>::iterator it = school.begin(); it != school.end(); ++it)
        {
            size_t dash_pos = it->first.find('-');
            int a = stoi(it->first.substr(0, dash_pos));
            int b = stoi(it->first.substr(dash_pos + 1));
            string reverse_key = to_string(b) + "-" + to_string(a);
            if (school[reverse_key] != it->second)
            {
                possible = false;
                break;
            }
        }
        printf(possible ? "YES\n" : "NO\n");
    }
    return 0;
}