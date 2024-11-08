#include<stdio.h>
#include<math.h>

int main()
{
    double a,b,c,d;
    scanf("%lf %lf %lf",&a,&b,&c);
    d=sqrt(b*b-4*a*c);
    printf("x1=%.2lf\n",(-b+d)/2/a);
    printf("x2=%.2lf\n",(-b-d)/2/a);
    return 0;
}