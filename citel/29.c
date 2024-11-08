#include<stdio.h>

void main()
{
    char c;
    for(int i=0;i<3;i++)
    {
        c=getchar();
        putchar(c);
        putchar(' ');
    }
    putchar('\n');
}