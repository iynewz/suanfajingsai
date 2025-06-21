#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <utility> // for std::pair

using namespace std;
const int maxr = 10000 + 5;
const int maxc = 10 + 5;
int db[maxr][maxc];

map<pair<int, int>, int> row_data; // 比如 row_data[2] = {10, 20};
map<string, int> DBcache;          // key 是 string；value 是 ID
int id_counter = 0;                // 用于分配新 id

int get_id(string x)
{

    if (DBcache.count(x))
    {
        return DBcache[x]; // 如果 x 已经存在，直接返回它的 id
    }
    else // 如果 x 不存在，分配新的 id
    {
        DBcache[x] = ++id_counter; // 要先++
        return id_counter;
    }
}

int main()
{
    int rows, columns;
    while (cin >> rows >> columns)
    {
        cin.ignore();
        // 初始化 id_counter
        id_counter = 0;
        DBcache.clear();

        // 读取并预处理数据，存入 db
        for (int i = 0; i < rows; i++)
        {
            string sentence, word;
            getline(cin, sentence);
            stringstream ss(sentence);
            int j = 0;
            while (getline(ss, word, ','))
            {                            // 按逗号分割
                db[i][j] = get_id(word); // 存入映射后的 id
                j++;
            }
        }
        // print db for test, 发现 db 错了
        // for (int i = 0; i < rows; i++)
        // {
        //     for (int j = 0; j < columns; j++)
        //     {
        //         cout << db[i][j];
        //     }
        //     cout << endl;
        // }

        int isPNF = 1;
        int r1_ans, r2_ans, c1_ans, c2_ans; // todo

        for (int c1 = 0; c1 < columns - 1; c1++)
        {
            if (isPNF == 0)
            {
                break;
            }
            for (int c2 = c1 + 1; c2 < columns; c2++)
            {
                row_data.clear();
                if (isPNF == 0)
                {
                    break;
                }
                for (int r = 0; r < rows; r++)
                {
                    pair<int, int> c1_c2_pair = make_pair(db[r][c1], db[r][c2]);
                    if (row_data.count(c1_c2_pair))
                    {
                        isPNF = 0;
                        r2_ans = r;
                        r1_ans = row_data[c1_c2_pair];
                        c1_ans = c1;
                        c2_ans = c2;
                        break;
                    }
                    else
                    {
                        row_data[c1_c2_pair] = r;
                    }
                }
            }
        }
        isPNF ? cout << "YES" << endl : cout << "NO" << '\n'
                                             << (r1_ans + 1) << " " << (r2_ans + 1) << '\n'
                                             << (c1_ans + 1) << " " << (c2_ans + 1) << endl;
    }
    return 0;
}