#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_Len 255

typedef unsigned char StringType[Max_Len+1];

//模仿strcmp实现该功能
int StrCompare(StringType s,StringType t)
{
    int min_len=(s[0]<t[0]) ? s[0] :t[0];
    for(int i=1;i<=min_len;i++)
    {
        if(s[i]!=t[i])
        return s[i]-t[i];
    }
    return s[0]-t[0];
}

int main()
{
    StringType s={5,'h','e','l','l','o'},t={5,'w','o','r','l','d'};
    int result=StrCompare(s,t);
    if(result>0)
        printf("s>t\n");
    else if(result==0)
        printf("s=t\n");
    else
        printf("s<t\n");

    return 0;
}