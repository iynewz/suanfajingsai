// IP Networks, UVa1590
#include <stdio.h>
#include <string.h>

#define maxn 1050 // m 的最大值

int byte[4][maxn];    // 存储 IP 地址的四个十进制字节
char binary[maxn][9]; // 存储 m 个二进制字符串
int mask[5];

void int2binary(int n, char *binary_str)
{
    // 将整数 n 转换为二进制字符串并打印
    for (int i = 7; i >= 0; i--)
    {
        binary_str[i] = (n % 2) + '0'; // 将剩余位转换为字符
        n /= 2;
    }
}

int main()
{
    int m;
    while (scanf("%d", &m) == 1)
    {
        memset(byte, 0, sizeof(byte));
        memset(binary, 0, sizeof(binary));
        memset(mask, 0, sizeof(mask));
        for (int i = 0; i < m; i++)
        {

            // 读取形如 194.85.160.177 的IP地址
            int a, b, c, d;
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            byte[0][i] = a;
            byte[1][i] = b;
            byte[2][i] = c;
            byte[3][i] = d;
        }

        // 检查输入的 m 个十进制网络地址，从左往右找到第一个不同的十进制值
        int first_diff_index = -1;
        for (int i = 0; i < 4; i++)
        {
            int curr_byte = byte[i][0]; // 比较的基准
            for (int j = 1; j < m; j++)
            {
                if (byte[i][j] != curr_byte)
                {
                    first_diff_index = i;
                    break; // 跳出 j 的循环
                }
            }
            if (first_diff_index != -1)
            {
                break; // 跳出 i 的循环
            }
        }

        for (int i = 0; i < m; i++)
        {
            int2binary(byte[first_diff_index][i], binary[i]);
        }

        // 把第一个不同的十进制位置的 m 个十进制都转成二进制。

        // 从左往右找到第一个不同的二进制字符
        int first_diff_char_index = -1;
        for (int i = 0; i < 8; i++)
        {
            char curr_char = binary[0][i];
            for (int j = 1; j < m; j++)
            {
                if (binary[j][i] != curr_char)
                {
                    first_diff_char_index = i;
                    break;
                }
            }
            if (first_diff_char_index != -1)
            {
                break;
            }
        }
        // 拼接 mask
        // 处理 first_diff_index 的左边
        for (int i = 0; i < first_diff_index; i++)
        {
            mask[i] = 255;
        }
        // 计算第 first_diff_index 位的 mask
        int temp = 0;
        for (int i = 0; i < first_diff_char_index; i++)
        {

            temp += 1 << (7 - i);
        }
        mask[first_diff_index] = temp;
        // 处理 first_diff_index 的右边
        for (int i = first_diff_index + 1; i < 4; i++)
        {
            mask[i] = 0;
        }

        if (first_diff_index == -1)
        {
            mask[0] = mask[1] = mask[2] = mask[3] = 255;
        }

        // print address
        for (int i = 0; i < 4; i++)
        {
            printf("%d", byte[i][0] & mask[i]);
            if (i != 3)
            {
                printf(".");
            }
        }
        printf("\n");
        // print mask
        for (int i = 0; i < 4; i++)
        {
            printf("%d", mask[i]);
            if (i != 3)
            {
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}