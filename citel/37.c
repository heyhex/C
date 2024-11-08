#include<stdio.h>

int main()
{
    double a,b,rate;
    scanf("%lf %lf",&a,&b);
    rate=b/a;
    printf("%.3lf%%",rate);
    return 0;
}