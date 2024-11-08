#include<stdio.h>
#include<stdlib.h>
#include"2.6.h"


//初始化双向循环链表：使得它的next和prior指向自己
void Initial(DuLinklist *L)
{
    *L=(DuLinklist)malloc(sizeof(DuLinklist));
    if(!L)
        perror("Failed!");
    (*L)->next=(*L)->prior=*L;
}

//插入：先后继再前驱（顺序不可更改），再修改prior
void Insert(DuLinklist *L)
{
    int n,data;
    DuLinklist p,s;
    printf("Enter the number of list:");
    scanf("%d",&n);
    printf("Enter the data:");
    for(int i=0;i<n;i++)
    {
        s=(DuLinklist)malloc(sizeof(DuLinklist));
        if(!s)
            perror("Failed!");
        
        scanf("%d",&data);
        s->data=data;
        s->freq=0;

        p=(*L)->prior;
        s->next=p->next;
        p->next=s;
        s->next->prior=s;
        s->prior=p;
    }
}

//2.6题目要求
void Locate(DuLinklist *L,int x)
{
    DuLinklist p,s;
    int i=1;

    //判断是否为空表
    if(!L || (*L)->next==L)
        perror("Empty!");
    //准备开始遍历寻找
    s=(*L)->next;
    while(s!=L && s->data!=x)
    {
        i++;
        s=s->next;
    }
    //已经到达头结点说明没有找到
    if(s==L)
        perror("Not Found!");
    else
    {
        s->freq++;
        //相当于把当前节点单拎出来准备好插入
        s->prior->next=s->next;
        s->next->prior=s->prior;
    }
    p=(*L)->next;
    //遍历寻找比该节点访问次数还大的结点
    while(p!=L && p->freq <s->freq)
        p=p->next;
    if(p==L)
    {
        //当该结点的访问次数最大的话就插入到该表的末尾
        s->next=p;
        p->prior->next=s;
        s->prior=p->prior;
        p->prior=s;
    }
    else
    {
        //如果找到了访问次数比该结点大的结点，把当前节点插入到p的前面
        s->next=p;
        p->prior->next=s;
        s->prior=p->prior;
        p->prior=s;
    }
}

//删除：先找到结点再依次修改指向
void Delete(DuLinklist *L,int i,int *e)
{
    DuLinklist p=(*L)->next,s;
    for(int j=1;j<i-1;j++)
    {
        if(p==L)
        {
            perror("Not Found!");
            break;
        }
        p=p->next;
    }
    s=p->next;
    p->next=s->next;
    s->next->prior=p;
    *e=s->data;
    free(s);
}

int main()
{
    return 0;
}