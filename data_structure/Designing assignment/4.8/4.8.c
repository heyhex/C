#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_Len 255

typedef unsigned char StringType[Max_Len+1];

int Match(StringType s,StringType t,int start)
{
    int ls=s[0],lt=t[0];
    if(start+lt-1>ls)
        return 0;
    for(int i=1;i<=lt;i++)
    {
        if(s[start+i-1]!=t[i])
            return 0;
    }
    return 1;
}

void Replace(StringType *s,StringType t,StringType v)
{
    int ls=(*s)[0],lt=t[0],lv=v[0];
    StringType result;
    result[0]=0;

    //初始位置
    int i=1;
    while(i<=ls)
    {
        if(Match(*s,t,i))
        {
            //超出部分截断
            if(result[0]+lv>Max_Len)
                break;
            for(int j=1;j<=lv;j++)
            {
                result[0]++;
                result[result[0]]=v[j];
            }
            i+=lt;
        }
        else
        {
            if(result[0]+1>Max_Len)
                break;
            result[0]++;
            result[result[0]]=(*s)[i];
            i++;
        }
    }

    //将后续字符加入
    for(int i=0;i<=result[0];i++)
        (*s)[i]=result[i];
}

int main()
{
    StringType s={6,'a','b','c','a','a','b'};
    StringType t={1,'a'};
    StringType v={3,'o','o','o'};

    Replace(&s,t,v);
    for(int i=1;i<=s[0];i++)
        printf("%c ",s[i]);

    return 0;
}