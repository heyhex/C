#include<stdio.h>

int main()
{
    int x,a,y,b;
    scanf("%d %d %d %d",&x,&a,&y,&b);
    printf("%.2lf",(double)(y*b-x*a)/(b-a));
    return 0;
}