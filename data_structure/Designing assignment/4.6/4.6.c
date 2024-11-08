#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_Len 255

typedef unsigned char StringType[Max_Len+1];

void StrAssign(StringType *t,char chars[])
{
    (*t)[0]=strlen(chars);
    for(int i=1;i<=*t[0];i++)
        (*t)[i]=(unsigned char)chars[i-1];
    (*t)[(*t)[0]+1]='\0';
}

int main()
{
    StringType t;
    char chars[]={"hello world!"};
    StrAssign(&t,chars);
    printf("the length of t: %d\n",t[0]);
    for(int i=1;i<=t[0];i++)
        printf("%c",t[i]);

    return 0;
}