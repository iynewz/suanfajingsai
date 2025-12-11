#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    system("g++ -O2  data.cpp -o data");
    system("g++ -O2 -std=c++17  7-12-ac.cpp -o std");
    system("g++ -O2 -std=c++17  7-12.cpp -o my");

    for (int t = 1; t <= 20000; t++)
    {
        cout << "Test #" << t << endl;

        // 1. 生成随机数据
        system("./data > input.txt");

        // 2. 跑别人 AC 的解
        system("./std < input.txt > std.txt");

        // 3. 跑我的解法
        system("./my < input.txt > my.txt");

        // 4. 比较
        if (system("diff std.txt my.txt > diff.txt"))
        {
            cout << "❌ Found difference!\n";
            cout << "Input:\n";
            system("cat input.txt");
            cout << "\nYour output:\n";
            system("cat my.txt");
            cout << "\nCorrect output:\n";
            system("cat std.txt");
            break;
        }
    }

    return 0;
}
