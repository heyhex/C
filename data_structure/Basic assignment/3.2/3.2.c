#include<stdio.h>
#include<stdlib.h>
#include"3.2.h"
#define STACK_INIT_SIZE 100; 
#define STACKINCREMENT 10;

//顺序存储
//初始化
void Initial_Sq(SqStack *S)
{
    S->data=(char*)malloc(sizeof(char)*Max_Size);
    if(!S)
        exit(1);
    S->top=-1;
}

//进栈
int Push_Sq(SqStack *S,char e)
{
    if(S->top>=Max_Size-1)
        return 0;
    S->top++;
    S->data[S->top]=e;
    return 1;
}

//出栈
int Pop_Sq(SqStack *S,char *e)
{
    if(S->top<0)
        return 0;
    *e=S->data[S->top];
    S->top--;
    return 0;
}

//获取栈顶元素
int GetTop_Sq(SqStack S,char *e)
{
    if(S.top<0)
        return 0;
    *e=S.data[S.top];
    return 1;
}

//判断栈空
int IfEmpty_Sq(SqStack S)
{
    if(S.top<0)
        return 1;
    else
        return 0;
}

//第二种顺序存储很少用

//共享存储
//进栈
void Push_SqDul(SqDulStack *S,char e,int number)
{
    if(S->top1==S->top2-1)
        exit(1);
    else if(number==1)
    {
        S->top1++;
        S->data[S->top1]=e;
    }
    else
    {
        S->top2--;
        S->data[S->top2]=e;
    }
}

//出栈
void Pop_SqDul(SqDulStack *S,char *e,int number)
{
    if(number==1)
    {
        if(S->top1==-1)
            exit(1);
        else
        {
            *e=S->data[S->top1];
            S->top1--;
        }
    }
    else
    {
        if(S->top2==Max_Size)
            exit(1);
        else
        {
            *e=S->data[S->top2];
            S->top2--;
        }
    }
}

//链式存储：很少使用
//进栈
void Push_LS(LinkStack top,char e)
{
    LinkStack p=(LinkStack)malloc(sizeof(SNode));
    if(!p)
        exit(1);
    p->data=e;
    p->next=top;
    top=p;
}

//出栈
void Pop_LS(LinkStack top,char *e)
{
    if(top==NULL)
        exit(1);
    LinkStack p=(LinkStack)malloc(sizeof(SNode));
    if(!p)
        exit(1);
    p=top;
    top=top->next;
    *e=p->data;
    free(p);
}