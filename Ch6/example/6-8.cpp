#include <sstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;
const int maxv = 10000 + 10;
int in_order[maxv], post_order[maxv];
int left_children[maxv], right_children[maxv];
int best;
int best_sum = 100000000;

int n;
bool read_list(int *a)
{
    string line;
    if (!getline(cin, line))
    {
        return false;
    }
    stringstream ss(line);
    int x;
    n = 0;
    while (ss >> x)
    {
        a[n++] = x;
    }
    return true;
}

int build(int l1, int r1, int l2, int r2)
{
    if (l1 > r1)
    {
        return 0;
    }
    int root = post_order[r2];
    int p = l1;
    while (in_order[p] != root)
    {
        p++;
    }
    int left_tree_cnt = p - l1;
    left_children[root] = build(l1, p - 1, l2, l2 + left_tree_cnt - 1);
    right_children[root] = build(p + 1, r1, l2 + left_tree_cnt, r2 - 1);
    return root;
}

void dfs(int u, int sum) // u: 当前遍历到的节点; sum: 从根到当前节点 u 的父节点的路径和
{
    sum += u;
    if (!left_children[u] && !right_children[u]) // 叶子
    {
        if (sum < best_sum || (sum == best_sum && u < best))
        {
            best = u;
            best_sum = sum;
        }
    }
    if (left_children[u])
        dfs(left_children[u], sum);
    if (right_children[u])
        dfs(right_children[u], sum);
}

int main()
{
    while (read_list(in_order))
    {
        read_list(post_order);
        build(0, n - 1, 0, n - 1);
        best_sum = 100000000;
        dfs(post_order[n - 1], 0);
        cout << best << "\n";
    }
    return 0;
}