#include<stdio.h>
#include<malloc.h>

int main()
{
    int n,sum,i;
    int *p;
    printf("enter n: ");
    scanf("%d",&n);
    if((p=(int *)calloc(n,sizeof(int)))==NULL)
    {
        printf("error!\n");
        return -1;
    }
    printf("enter numbers: ");
    for(i=0;i<n;i++)
        scanf("%d",p+i);
    sum=0;
    for(i=0;i<n;i++)
        sum+=*(p+i);
    printf("the sum is %d.\n",sum);
    free(p);

    return 0;
}