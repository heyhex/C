#include<stdio.h>

int main()
{
    double a,b,s;
    scanf("%lf %lf %lf",&a,&b,&s);
    printf("%d",(int)(s+b/a*s));

    return 0;
}