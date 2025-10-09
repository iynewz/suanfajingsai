#include <iostream>
#include <cstring>

const int len = 32; // 图像尺寸 32x32
const int maxn = 1024 + 10;
char s[maxn];
int buf[len][len];
int cnt; // 统计黑色像素数量

// 解析四叉树编码并绘制到buf中
// 参数：
//   s: 四叉树编码字符串
//   p: 当前解析位置（引用传递，用于递归时推进）
//   r, c: 当前区域左上角坐标
//   w: 当前区域宽度
void draw(const char *s, int &p, int r, int c, int w)
{
    char ch = s[p];
    p++;
    if (ch == 'f') // 全黑
    {
        for (int i = r; i < r + w; i++)
        {
            for (int j = c; j < c + w; j++)
            {
                if (buf[i][j] == 0)
                {
                    buf[i][j] = 1;
                    cnt++;
                }
            }
        }
    }
    else if (ch == 'p') // 需要继续划分
    {
        int half = w / 2;
        draw(s, p, r, c + half, half);        // 右上
        draw(s, p, r, c, half);               // 左上
        draw(s, p, r + half, c, half);        // 左下
        draw(s, p, r + half, c + half, half); // 右下
    }
    // 如果是 'e'（全白），什么都不做
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(buf, 0, sizeof(buf));
        cnt = 0;
        for (int i = 0; i < 2; i++) // 处理两个四叉树
        {
            scanf("%s", s);
            int p = 0;
            draw(s, p, 0, 0, len);
        }
        printf("There are %d black pixels.\n", cnt);
    }
    return 0;
}