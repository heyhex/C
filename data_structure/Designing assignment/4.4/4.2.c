#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct String
{
    char *ch;
    int length;
}StringType;

//将s的值赋给t, 实际参数s可以是串变量或串常量
void StrAssign(StringType *s, StringType source) 
{
    if (s->ch != NULL) 
    {
        // 释放之前的内存
        free(s->ch); 
    }
    
    s->ch = (char *)malloc(source.length + 1);
    strcpy(s->ch, source.ch);
    s->length = source.length;
}

//比较s和t。若s>t，返回值>0；若s=t，返回值=0；若s<t，返回值<0
int StrCompare(StringType s,StringType t)
{
    int result=strcmp((s.ch),(t.ch));
    return result;
}

//返回s中的元素个数，即该串的长度
int StrLength(StringType s)
{
    return s.length;
}

//返回由s和t联接而成的新串
StringType Concat(StringType s,StringType t)
{
    StringType new;
    new.length=s.length+t.length;
    new.ch=(char*)malloc(sizeof(char)*(new.length+1));
    if(!new.ch)
        exit(1);
    int i=0;
    while(i<s.length)
    {
        new.ch[i]=s.ch[i];
        i++;
    }
    int j=0;
    while(j<t.length)
    {
        new.ch[i+j]=t.ch[j];
        j++;
    }
    new.ch[new.length]='\0';

    return new;
}

//当1≤start≤StrLength(s)，且0≤len≤StrLength(s)-start+1时，
//返回s中第start个字符起长度为len的子串，否则返回空串
StringType SubString(StringType s,int start,int len)
{
    StringType result;
    if(start<0 || start>StrLength(s) || len<=0 ||len>StrLength(s)-start+1)
    {
        result.ch=NULL;
        result.length=0;
    }
    else
    {
        result.ch=(char*)malloc(sizeof(char)*len+1);
        if(!result.ch)
            exit(1);
        result.length=len;
        for(int i=start-1;i<start+len-1;i++)
            result.ch[i-start+1]=s.ch[i];
        result.ch[result.length]='\0';
    }
    return result;
}

/*
调试用
int main()
{
    StringType s,t,new,sub_s;
    char arr1[10]={"abcde"};
    char arr2[10]={"fghik"};
    s.ch=(char*)malloc(sizeof(char)*5);
    t.ch=(char*)malloc(sizeof(char)*5);
    for(int i=0;i<5;i++)
    {
        s.ch[i]=arr1[i];
        t.ch[i]=arr2[i];
    }
    s.length=t.length=5;
    printf("%d\n",StrCompare(s,t));
    StrAssign(&s,t);
    printf("%d\n",StrCompare(s,t));
    printf("%d %d\n",StrLength(s),StrLength(t));
    new=Concat(s,t);
    printf("%d",StrLength(new));
    sub_s=SubString(new,3,4);

    return 0;
}*/