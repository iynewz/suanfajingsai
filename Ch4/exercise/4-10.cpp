// Flood, UVa 815
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 910
#define cell_size 100 // 每个格子底面积100平方米

int elevations[maxn];

int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m, total_water;
    int region_count = 1;
    while (scanf("%d %d", &n, &m) == 2 && n != 0 && m != 0)
    {
        int total_cells = n * m;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                scanf("%d", &elevations[i * m + j]);
            }
        }
        scanf("%d", &total_water);

        qsort(elevations, total_cells, sizeof(int), comp);

        double remaining_water = total_water;
        float sea_level = 0.0f;
        int current_height = elevations[0];
        int i_index = 0; // 当前处理的位置索引

        if (total_water == 0)
        {
            sea_level = current_height;
        }
        else
        {
            while (i_index < total_cells - 1)
            {
                int j = i_index + 1;
                // 跳过所有相同高度的网格
                while (j < total_cells && elevations[j] == current_height)
                {
                    j++;
                }

                // 已到达数组末尾（所有网格高度相同）
                if (j >= total_cells)
                    break;

                int next_height = elevations[j];
                int diff = next_height - current_height;
                // 当前被淹没的网格数 = j（0到j-1的网格）
                double water_needed = (double)diff * j * cell_size;

                if (remaining_water < water_needed)
                {
                    // 水量不足：计算最终水位
                    sea_level = current_height + remaining_water / (j * cell_size);
                    remaining_water = 0;
                    break;
                }
                else
                {
                    // 消耗水量并提升水位
                    remaining_water -= water_needed;
                    current_height = next_height;
                    i_index = j; // 移动到下一个高度区域
                }
            }

            // 仍有剩余水量（所有网格已被淹没）
            if (remaining_water > 0)
            {
                sea_level = current_height + remaining_water / (total_cells * cell_size);
            }
        }

        // 统计被淹没的网格数
        int count = 0;
        for (int k = 0; k < total_cells; k++)
        {
            if ((float)elevations[k] <= sea_level)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        float percentage = (float)count * 100 / total_cells;

        // 输出结果
        printf("Region %d\n", region_count++);
        printf("Water level is %.2f meters.\n", sea_level);
        printf("%.2f percent of the region is under water.\n\n", percentage);
    }
    return 0;
}