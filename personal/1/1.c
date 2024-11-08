#include<stdio.h>

int prime(int i)
{
    if(i==1)
        return 0;
    for(int m=2;m*m<=i;m++)
    {
        if(i%m==0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    for(int i=2;i<=100;i++)
        if(prime(i))
            printf("%d\n",i);

    return 0;
}