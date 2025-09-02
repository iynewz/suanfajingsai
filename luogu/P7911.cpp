// 10
// Server 192.168.1.1:80
// Client 192.168.1.1:80
// Client 192.168.1.1:8080
// Server 192.168.1.1:80
// Server 192.168.1.1:8080
// Server 192.168.1.999:0
// Client 192.168.1.1.8080
// Client 192.168.1.1:8080
// Client 192.168.1.1:80
// Client 192.168.1.999:0

#include <iostream>
#include <map>

using namespace std;

int n;
struct Node
{
    bool isServer;
    string ad;
    string rep; // 输出
};

Node nodes[1005];
map<string, long long> server_mp;

bool ad_validation(string s)
{
    // 192.168.1.1:99999
    int time = 4;
    int i = 0;
    int dot_count = 0, colon_count = 0;

    while (time--)
    {
        long long a = 0;
        while (1)
        {
            if (s[i] > '9' || s[i] < '0')
            {
                return false;
            }
            a += s[i] - '0';
            i++;

            if (s[i] == '.')
            {
                i++;
                dot_count++;
                if (colon_count > 0)
                {
                    return false;
                }
                break; // break 内层的 while
            }
            if (s[i] == ':')
            {
                i++;
                colon_count++;
                break; // break 内层的 while
            }
            else
            {
                if (a == 0)
                {
                    return false; // 这时候处理前导 0
                }
                a *= 10;
            }
        }
        if (a < 0 || a > 255)
        {
            return false;
        }
    }
    if (dot_count != 3 || colon_count != 1)
    {
        return false;
    }

    long long mask = 0;
    while (1)
    {
        mask += s[i] - '0'; // 这里不要漏了 - ‘0’
        i++;
        if (s[i] == '\0')
        {
            break;
        }
        else
        {
            if (mask == 0)
            {
                return false; // 这时候处理前导 0
            }
            mask *= 10;
        }
    }
    if (mask > 65535 || mask < 0)
    {
        return false;
    }
    return true;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s, ad;
        cin >> s >> ad;
        Node curr;
        bool isValid = ad_validation(ad);
        if (!isValid)
        {
            curr.rep = "ERR";
            nodes[i] = curr; // 不要忘记这里赋值
            continue;
        }
        if (s == "Server")
        {
            curr.isServer = true;
            if (server_mp.find(ad) != server_mp.end()) // 重复的 server
            {
                curr.rep = "FAIL";
                nodes[i] = curr;
                continue;
            }
            else
            {
                server_mp.insert({ad, i});
                curr.rep = "OK";
            }
        }
        else // Client
        {
            curr.isServer = false;
            auto it = server_mp.find(ad);
            if (it != server_mp.end())
            {
                curr.rep = to_string(it->second); // to_string
            }
            else
            {
                curr.rep = "FAIL";
            }
        }
        nodes[i] = curr;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << nodes[i].rep << endl;
    }

    return 0;
}