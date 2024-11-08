#include<stdio.h>
#include<stdlib.h>
#include"base.h"

//栈的基本操作
void Initial(Stack *S)
{
    S->base=(Elem *)malloc(sizeof(Elem)*Initial_Size);
    if(!S->base)
        exit(1);
    S->top=S->base;
    S->size=Initial_Size;
}

int Empty(Stack S)
{
    if(S.top==S.base)
        return 1;
    else
        return 0;
}

int GetTop(Stack S,Elem *e)
{
    if(Empty(S)==1)
    {
        printf("Empty!\n");
        return 0;
    }
    else
    {
        e=S.top-1;
        return 1;
    }
}

int Length(Stack S)
{
    return S.top-S.base;
}

void Push(Stack *S,Elem e)
{
    //分配新内存
    if(S->top-S->base>=S->size)
    {
        S->base=(Elem *)realloc(S->base,sizeof(Elem)*(S->size+Increment));
        if(!S->base)
            exit(1);
        S->top=S->base+S->size;
        S->size+=Increment;
    }
    *(S->top)=e;
    S->top++;
}

int Pop(Stack *S,Elem *e)
{
    if(Empty(*S)==1)
    {
        printf("Empty!\n");
        return 0;
    }
    *e=*(S->top-1);
    S->top--;
    return 1;
}