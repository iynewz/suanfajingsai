#include <stdio.h>

int main() 
{
    int a, b, c, case_num = 1;  // Use a valid variable name (not "case")
    while (scanf("%d%d%d", &a, &b, &c) == 3) 
    {
        int found = 0;
        for (int i = 10; i <= 100; i++) 
        {
            if (i % 3 == a && i % 5 == b && i % 7 == c) 
            {
                printf("Case %d: %d\n", case_num, i);
                found = 1;
                break;  // Exit early once a solution is found
            }
        }
        if (!found) 
        {
            printf("Case %d: No answer\n", case_num);
        }
        case_num++;  // Increment case number for every input line
    }
    return 0;
}
