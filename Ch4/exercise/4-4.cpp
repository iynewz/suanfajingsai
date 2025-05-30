// UVa253
#include <stdio.h>
#include <string.h>

// 沿着 x 轴旋转：3，4 不变，1 -> 2, 2 -> 6, 6 -> 5, 5 -> 1 // 0 1 2 3 4 5
// i - 1: 沿着 x 轴旋转：2，3 不变，0 -> 1, 1 -> 5, 5 -> 4, 4 -> 0 // 1 5 2 3 0 4
void x_transfer(char *str) // 修改原字符串
{
    char temp[6] = {str[1], str[5], str[2], str[3], str[0], str[4]};
    for (int i = 0; i < 6; i++)
    {
        str[i] = temp[i];
    }
}

void y_transfer(char *str)
{
    char temp[6] = {str[0], str[3], str[1], str[4], str[2], str[5]};
    for (int i = 0; i < 6; i++)
    {
        str[i] = temp[i];
    }
}

void z_transfer(char *str)
{
    char temp[6] = {str[3], str[1], str[0], str[5], str[4], str[2]};
    for (int i = 0; i < 6; i++)
    {
        str[i] = temp[i];
    }
}

int main()
{
    char a[7];
    char b[7];
    // input is like rbgggrrggbgr
    while (scanf("%6s%6s", a, b) == 2)
    {
        // printf("a: %s\n", a);
        // printf("b: %s\n", b);
        int found = 0;
        for (int x = 0; x < 4; x++)
        {
            x_transfer(a);
            for (int y = 0; y < 4; y++)
            {
                y_transfer(a);
                for (int z = 0; z < 4; z++)
                {
                    z_transfer(a);
                    if (strcmp(a, b) == 0)
                    {
                        found = 1;
                        break;
                    }
                }
            }
        }
        if (found)
        {
            printf("TRUE\n");
        }
        else
        {
            printf("FALSE\n");
        }
    }
    return 0;
}