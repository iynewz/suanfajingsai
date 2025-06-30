#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void parse(const string &s, string &user, string &mta)
{
    std::size_t found = s.find("@");
    user = s.substr(0, found);
    mta = s.substr(found + 1);
    // cout << s << found << " " << user << " " << mta << endl;
}
int main()
{
    int k;
    string s, mta, receiver, text;
    string user_sender, mta_sender, user_receiver, mta_receiver;
    set<string> addr; // Fiona@London, Paul@London
    // MTA London 4 Fiona Paul Heather Nevil
    while (cin >> s && s != "*") // input 第七行的 “*” 会在这里被吃掉
    {
        cin >> mta >> k;
        for (int i = 0; i < k; i++)
        {
            string user;
            cin >> user;
            addr.insert(user + "@" + mta);
        }
    }
    while (cin >> s && s != "*") // 进入 input 第八行
    {
        parse(s, user_sender, mta_sender);
        vector<string> mta;               // 按输入顺序放 mta
        map<string, vector<string>> dest; // 每个 mta 对应的 receiver
        set<string> visited;

        while (cin >> receiver && receiver != "*")
        {
            parse(receiver, user_receiver, mta_receiver);
            if (visited.count(receiver))
            {
                continue;
            }
            else
            {
                visited.insert(receiver);
                if (!dest.count(mta_receiver))
                {
                    mta.push_back(mta_receiver);
                }
                dest[mta_receiver].push_back(receiver);
            }
        }
        cin.ignore(); // 跳过下一个字符（即换行符）

        string data;
        while (getline(cin, text) && text[0] != '*')
        {
            data += "     " + text + "\n";
        }
        // print data
        for (int i = 0; i < mta.size(); i++)
        {
            string mta2 = mta[i];
            vector<string> users = dest[mta2];
            cout << "Connection between " << mta_sender << " and " << mta2 << endl;
            cout << "     HELO " << mta_sender << "\n"
                 << "     250\n"
                 << "     MAIL FROM:<" << s << ">\n"
                 << "     250\n";
            bool is_valid = false;
            for (int j = 0; j < users.size(); j++)
            {
                string curr_receiver = users[j];
                cout << "     RCPT TO:<" << curr_receiver << ">" << "\n";
                if (addr.count(curr_receiver))
                {
                    is_valid = true;
                    cout << "     250\n";
                }
                else
                {
                    cout << "     550\n";
                }
            }
            if (is_valid)
            {
                cout << "     DATA\n"
                     << "     354\n"
                     << data << "     .\n"
                     << "     250\n";
                // process data only when valid receiver exists
            }
            cout << "     QUIT\n"
                 << "     221" << endl;
        }
    }

    // print addr
    // for (set<string>::iterator it = addr.begin(); it != addr.end(); ++it)
    // {
    //     cout << *it << endl; // 输出字典中的单词
    // }

    return 0;
}