#include<stdio.h>
#include<string.h>
#include"3.2.c"

int pair()
{
    //创建一个栈并且初始化
    SqStack *S=(SqStack*)malloc(sizeof(SqStack));
    if(!S)
        exit(1);
    Initial_Sq(S);
    char c,ch,string[Max_Size]={0};
    int is_pair=0;
    //储存字符串
    printf("Enter an expression:");
    for(int i=0;i<Max_Size;i++)
    {
        //用c接受输入的字符
        c=getchar();
        if(c=='\n')
            break;
        else
            string[i]=c;
    }

    for(int i=0,length=strlen(string);i<length;i++)
    {
        if(string[i]=='(' || string[i]=='[' || string[i]=='{')
        {
            Push_Sq(S,string[i]);
        }
        else if(string[i]==')' || string[i]==']' || string[i]=='}')
        {
            //判断是不是空
            if(IfEmpty_Sq(*S))
            {
                printf("Wrong Pair!\n");
                return 0;
            }
            //查找栈顶元素
            GetTop_Sq(*S,&ch);
            if(ch=='(')
            {
                if(string[i]==')')
                {
                    Pop_Sq(S,&ch);
                    is_pair=1;
                }
                
            }
            else if(ch=='[')
            {
                if(string[i]==']')
                {
                    Pop_Sq(S,&ch);
                    is_pair=1;
                }
            }
            else if(ch=='{')
            {
                if(string[i]=='}')
                {
                    Pop_Sq(S,&ch);
                    is_pair=1;
                }
            }
        }
    }
    if(IfEmpty_Sq(*S)!=1)
        is_pair=0;
    
    if(is_pair==1)
    {
        printf("No Error!\n");
        return 1;
    }
    else
    {
        printf("Wrong Pair!\n");
        return 0;
    }
}

int main()
{
    pair();
    return 0;
}