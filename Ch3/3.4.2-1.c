#include<stdio.h>
#include <limits.h>
#include<stdlib.h>
// int main() {
//     int count = 0, n;
//     while(scanf("%d", &n) == 1) {
//         count++;
//     }
//     printf("总数：%d\n", count);
//     return 0;
// }

// 输入一些数，求最大值、最小值和平均数
// int main() {
//     int max = 0, min = INT_MAX, count = 0;
//     double sum = 0;
//     int n;
//     while(scanf("%d", &n) == 1) {
//         count++;
//         sum = sum + n;
//         if(n > max) {
//             max = n;
//         }
//         if(n < min) {
//             min = n;
//         }
//     }
//     printf("最大值：%d\n最小值：%d\n平均数：%.2f\n", max, min, sum / count);
//     return 0;
// }

// 输入一些数，哪两个数最接近
// int main() {
//     int min_diff = INT_MAX, a = 0, b = 0;
//     int nums[1000], count = 0;
//     while(scanf("%d", &nums[count]) == 1) {
//         count++;
//     }
//     for(int i = 0; i < count; i++){
//         for(int j = i + 1; j < count; j++) {
//             int curr_diff = abs(nums[i] - nums[j]);
//             if(curr_diff < min_diff) {
//                 min_diff = curr_diff;
//                 a = nums[i];
//                 b = nums[j];
//             }
//         }
//     }
//     printf("最接近的两个数：%d，%d\n", a, b);
//     return 0;
// }

//输入一些数，求第二大的值
int main() {
    int max = INT_MIN, second_max = INT_MIN, n;
    while(scanf("%d", &n) == 1) {
        if (n > max) {
            second_max = max; // i forgot this
            max = n;
        } else if( n > second_max && n != max) {
            second_max = n;
        }
    }
    printf("第二大的值：%d\n", second_max);
    return 0;
}


//输入一些数，求他们的方差
