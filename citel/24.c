#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<=n+1;i++)
    {
    if(2*i+4*(n-i)==m)
    {
        printf("%d %d",i,n-i);
        break;
    }
    if(i==n+1)
        printf("No answer\n");
    }
        

    return 0;
}