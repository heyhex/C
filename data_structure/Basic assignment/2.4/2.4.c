#include<stdio.h>
#include"2.4.h"

void Reverse(List *L)
{
    int temp=0;
    for(int i=0;i<=L->length/2;i++)
    {
        temp=L->a[i];
        L->a[i]=L->a[L->length-i-1];
        L->a[L->length-i-1]=temp;
    }
}

void ReverseList(List *L)
{
    int i=0;
    int j=L->length-1;
    while(i<j)
    {
        
    }
}