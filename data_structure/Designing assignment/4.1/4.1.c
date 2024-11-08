#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct String
{
    char *ch;
    int length;
}String;

void Create(String *S)
{
    char arr[20];
    printf("Enter the string:");
    scanf("%s",arr);
    
    //分配内存
    S->ch=(char *)malloc(sizeof(char)*strlen(arr));
    if(!S->ch)
        exit(1);
    S->length=strlen(arr);
    for(int i=0;i<S->length;i++)
        S->ch[i]=arr[i];
}

char* Next(String S)
{
    char *next;
    int length=S.length;
    next=(char *)malloc(sizeof(char)*length);
    int j=1;
    //初始化next的值
    next[1]=0;
    next[2]=1;
    for(int i=3;i<=length;i++)
    {
        while(j>1 && S.ch[i-2]!=S.ch[j-1])
            j=next[j-1];
        if(S.ch[i-2]==S.ch[j-1])
            j++;
        next[i]=j;
    }
    return next;
}

int Index_KPM(String S,String Pat,int pos)
{
    //确定初始位置，i是主串，j是模式串
    int i=pos,j=1;
    char *next=Next(Pat);
    while(i<=S.length && j<=Pat.length)
    {
        if(j==0 || S.ch[i-1]==Pat.ch[j-1])
        {
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j>Pat.length)
        return i-Pat.length;
    else
        return 0;
}

int main()
{
    String S,Pat;
    Create(&S);
    Create(&Pat);
    printf("KMP result: %d",Index_KPM(S,Pat,1));

    return 0;
}