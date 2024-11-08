#include<stdio.h>
#include <math.h>

#define PI acos(-1)

int main()
{
    double r,h;
    scanf("%lf %lf",&r,&h);
    printf("Area = %.3lf",2*PI*r*r+2*PI*r*h);

    return 0;
}