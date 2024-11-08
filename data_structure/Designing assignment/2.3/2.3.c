#include<stdio.h>

void Move(int a[],int n,int k)
{
    printf("Before:\n");
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
    int temp;
    if(k%n!=0)
    {
        for(int i=0;i<k;i++)
        {
            temp=a[n-1];
            for(int j=n-1-1;j>=0;j--)
            {
                a[j+1]=a[j];
            }
            a[0]=temp;
        }
    }
    printf("After:\n");
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}

int main()
{
    int a[6]={1,2,3,4,5,6};
    Move(a,6,3);
    return 0;
}