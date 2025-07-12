#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

map<string, string> library; // 为了记录书的作者
set<string> shelved_books;   // 书架上剩下的书
set<string> returned_books;  // 待上架书籍
vector<string> A;            // 书架的最终形态

bool comp(const string &a, const string &b)
{
    string author_a = library[a];
    string author_b = library[b];
    if (author_a != author_b)
    {
        return author_a < author_b;
    }
    return a < b;
}

void shelve_books()
{
    A.clear();
    A.insert(A.end(), shelved_books.begin(), shelved_books.end());
    A.insert(A.end(), returned_books.begin(), returned_books.end());
    // sort A
    sort(A.begin(), A.end(), comp);
    for (int i = 0; i < A.size(); i++)
    {
        // if A[i] is in returned_books
        if (returned_books.count(A[i]))
        {
            returned_books.erase(A[i]);
            shelved_books.insert(A[i]);
            if (i == 0)
            {
                cout << "Put " << A[i] << " first" << endl;
            }
            else
            {
                cout << "Put " << A[i] << " after " << A[i - 1] << endl;
            }
        }
    }
    cout << "END" << endl;
}

int main()
{
    string line;

    while (getline(cin, line) && line != "END") // read book stock
    {
        size_t found = line.find(" by ");
        string title = line.substr(0, found);
        string author = line.substr(found + 4);
        library[title] = author;
        shelved_books.insert(title);
    }

    while (getline(cin, line) && line != "END") // read instructions
    {
        if (line[0] == 'B') // BORROW
        {
            size_t found = line.find(" ");
            string title = line.substr(found + 1);
            shelved_books.erase(title);
        }
        if (line[0] == 'R') // RETURN
        {
            size_t found = line.find(" ");
            string title = line.substr(found + 1);
            returned_books.insert(title);
        }
        if (line[0] == 'S') // SHELVE
        {
            shelve_books();
        }
    }
    return 0;
}