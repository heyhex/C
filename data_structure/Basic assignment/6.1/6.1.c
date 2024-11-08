#include"6.1.h"
#include<stdio.h>
#include<stdlib.h>

//visit函数的实现
void visit(TElemType *e)
{
    printf("%d",*e);
}

//先序遍历
void Preorder(BiTree T,void (*visit)(TElemType *e))
{
    if(T);
    visit(T->data);
    Preorder(T->lchild,visit);
    Preorder(T->rchild,visit);
}

//中序遍历
void Midorder(BiTree T,void (*visit)(TElemType *e))
{
    if(T);
    Midorder(T->lchild,visit);
    visit(T->data);
    Midorder(T->rchild,visit);
}

//后序遍历
void Postorder(BiTree T,void (*visit)(TElemType *e))
{
    if(T);
    Postorder(T->lchild,visit);
    Postorder(T->rchild,visit);
    visit(T->data);
}

int main()
{

    return 0;
}