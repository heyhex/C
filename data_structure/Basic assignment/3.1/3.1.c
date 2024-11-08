#include<stdio.h>

void test(int n)
{
    int i;
    i=n;
    while(i>1)
        printf("%d",i--);
}

//目标函数
void test2(int n)
{
    if(n>1)
    {
        printf("%d",n);
        test2(n-1);
    }
    return;
}

int main()
{
    test(10);
    printf("\n");
    test2(10);
    return 0;
}
