#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
struct node
{
    char c;
    int num;
} lit[110], mid[110]; // 小括号，中括号栈
int ltop, mtop, lnow = 1, mnow = 1;
string a;
char lef[110]; // 离当前右括号最近的左括号
int leftop;
int main()
{
    //	freopen("work.in","r",stdin);freopen("work.out","w",stdout);
    cin >> a;
    int n = a.length();
    for (int i = 0; i < n; i++)
    {
        if (a[i] == '(') // 左括号
        {
            lit[++ltop].num = i;
            lit[ltop].c = a[i];
            lef[++leftop] = a[i];
        }
        if (a[i] == ')') // 右括号
        {
            if (ltop && lit[ltop].c == '(' && lef[leftop] == '(')
                ltop--, leftop--;
            else
                lit[++ltop].num = i, lit[ltop].c = a[i];
        }
        // 下同
        if (a[i] == '[')
        {
            mid[++mtop].num = i;
            mid[mtop].c = a[i];
            lef[++leftop] = a[i];
        }
        if (a[i] == ']')
        {
            if (mtop && mid[mtop].c == '[' && lef[leftop] == '[')
                mtop--;
            else
                mid[++mtop].num = i, mid[mtop].c = a[i];
        }
    }
    // 输出
    for (int i = 0; i < n; i++)
    {
        bool f = false;
        if (i == lit[lnow].num && lnow <= ltop)
        {
            f = true;
            if (lit[lnow].c == '(')
                printf("%c)", a[i]);
            else
                printf("(%c", a[i]);
            lnow++; // 遍历
        }
        if (i == mid[mnow].num && mnow <= mtop)
        {
            f = true;
            if (mid[mnow].c == '[')
                printf("%c]", a[i]);
            else
                printf("[%c", a[i]);
            mnow++;
        }
        if (!f)
            printf("%c", a[i]); // 如果可以匹配，直接输出
    }
    //	fclose(stdin);fclose(stdout);
    return 0;
}