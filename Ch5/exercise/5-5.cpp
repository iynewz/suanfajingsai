// 5-5 Compound Words, UVa 10391
#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    string word;
    set<string> dict;
    set<string> answer;
    vector<string> words;
    while (cin >> word)
    {
        words.push_back(word);
        dict.insert(word);
    }

    vector<string>::const_iterator it;
    for (it = words.begin(); it != words.end(); it++)
    {
        string curr_word = *it;
        int size = curr_word.size();
        for (int i = 1; i < size; i++)
        {
            string prefix = curr_word.substr(0, i);
            string suffix = curr_word.substr(i);
            // cout << *it << " " << prefix << " " << suffix << endl;
            if (dict.count(prefix) && dict.count(suffix))
            {
                answer.insert(curr_word);
            }
        }
    }
    set<string>::const_iterator answer_it;
    for (answer_it = answer.begin(); answer_it != answer.end(); answer_it++)
    {
        cout << *answer_it << endl;
    }

    return 0;
}