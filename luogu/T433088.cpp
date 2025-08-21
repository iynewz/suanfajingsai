// 4
// a[] 20 40 30 10
// 插入排序
#include <iostream>
using namespace std;

int a[55];
int n;
int move_time = 0;

void insert(int *a, int n) // 把 index 为 n 的元素插入到已经排序好的序列里
{
    int k = a[n];
    while (k < a[n - 1])
    {
        a[n] = a[n - 1];
        n--;
        move_time++;
        if (n == 0)
        {
            break;
        }
    }
    a[n] = k;
}

void insert_sort()
{
    for (int i = 1; i < n; i++)
    {
        insert(a, i);
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    insert_sort();
    cout << move_time << endl;
    return 0;
}