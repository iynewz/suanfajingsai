// UVa140 Bandwidth
// Rujia Liu
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
// A:FB;B:GC;D:GC;F:AGH;E:HD
// #
// u : [0, 0, 1, 1, 3, 3, 5, 5, 5, 4, 4]
// v : [5, 1, 6, 2, 6, 2, 0, 6, 7, 7, 3]

const int maxn = 8 + 5;
int id[256], letter[maxn];

int main()
{
    char input[1000];
    while (scanf("%s", input) == 1 && input[0] != '#')
    {
        int n = 0; // 计算结点个数，出现了多少种不同的大写字母
        for (char searchChar = 'A'; searchChar <= 'Z'; searchChar++)
        {
            if (strchr(input, searchChar) != NULL)
            {
                id[searchChar] = n++;
                letter[id[searchChar]] = searchChar;
            }
        }

        int len = strlen(input);
        int p = 0, q = 0; // p 找冒号，q 找分号
        vector<int> u, v;
        while (true)
        {
            while (p < len && input[p] != ':')
            {
                p++;
            }
            if (p == len)
            {
                break;
            }
            while (q < len && input[q] != ';')
            {
                q++;
            }
            for (int i = p + 1; i < q; i++)
            {
                u.push_back(id[input[p - 1]]);
                v.push_back(id[input[i]]);
            }
            p++;
            q++;
        }
        // test
        //  printf("u: ");
        //  for(auto x : u) {
        //      printf("%d ", x);
        //  }
        //  printf("\nv: ");
        //  for(auto x : v) {
        //      printf("%d ", x);
        //  }

        int P[maxn]; // 当前尝试的排列
        int bestP[maxn];
        int pos[maxn];
        int ans = n;
        for (int i = 0; i < n; i++)
        {
            P[i] = i; // 初始化第一个排列
        }
        do
        {
            for (int i = 0; i < n; i++)
            {
                pos[P[i]] = i; // 计算每个节点在当前排列中的位置
            }
            int bindwidth = 0;
            for (int i = 0; i < u.size(); i++)
            {
                bindwidth = max(bindwidth, abs(pos[u[i]] - pos[v[i]]));
            }
            if (bindwidth < ans)
            {
                ans = bindwidth;
                memcpy(bestP, P, sizeof(P));
            }

        } while (next_permutation(P, P + n));

        for (int i = 0; i < n; i++)
        {
            printf("%c ", letter[bestP[i]]);
        }
        printf("-> %d\n", ans);
    }
    return 0;
}