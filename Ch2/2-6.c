#include<stdio.h>
int main()
{
    double sum = 0;
    for(int i = 1; ; i++) {
        double term = 1.0 / (i*2-1);
        if( i%2 == 1){
            sum += term;
        }else {
            sum -= term;
        }
        if(term < 1e-6) break;
    }
    printf("%f\n", sum);
    double term1 = 1.0 / (2*2 - 1);
    printf("%f\n", term1);
    return 0;
}