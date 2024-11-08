#include<stdio.h>
#include<stdlib.h>
#include"2.2.h"

//带头结点的单向循环链表
//（虽然题目中提到不需要头结点，但是头结点方便定位，并且对于空表和非空表来说操作一致）

//初始化：让头结点的数据域为空，next指向空
void Initial(CLinkList *L)
{
    *L=(CLinkList)malloc(sizeof(CLinkList));
    if(!L)
    {
        printf("Not Enough Space!");
        exit(1);
    }
    (*L)->next=NULL;
}

//头插法创建单循环链表：注意是逆序输入
void Create_Head(CLinkList *L)
{
    CLinkList s;
    int n,data=0;
    printf("Enter the number of people:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        //分配内存
        s=(CLinkList)malloc(sizeof(CLinkList));
        if(!s)
        {
            printf("Not Enough Space!");
            exit(1);
        }
        printf("Enter the data of NO.%d:",n-i+1);
        scanf("%d",&data);
        s->data=data;
        s->next=(*L)->next;
        (*L)->next=s;
    }
    //寻找最后一个结点
    while(s->next!=NULL)
        s=s->next;
    //将最后一个结点的next指向第一个结点（即头结点的下一个结点）
    s->next=(*L)->next;
}

//尾插法创建单向循环链表
void Create_Tail(CLinkList *L)
{
    CLinkList s,p;
    int n;
    printf("Enter the number of people:");
    scanf("%d",&n);
    p=*L;
    for(int i=0;i<n;i++)
    {
        //分配内存
        s=(CLinkList)malloc(sizeof(CLinkList));
        if(!s)
        {
            printf("Not Enough Space!");
            exit(1);
        }
        printf("Enter the data of NO.%d:",i+1);
        scanf("%d",&(s->data));
        s->next=NULL;
        p->next=s;
        p=s;
    }
    //将最后一个结点的next指向L的next
    p->next=(*L)->next;
}

int Josephus(CLinkList *L)
{
    int m,data=0;
    printf("Enter the initial number of this game:");
    scanf("%d",&m);
    //两个指针，便于删除结点
    CLinkList p,q;
    //p指向第一个结点，q指向最后一个结点
    p=(CLinkList)malloc(sizeof(CLinkList));
    q=(CLinkList)malloc(sizeof(CLinkList));
    q=p=(*L)->next;
    while(q->next!=p)
        q=q->next;
    //创建计数器
    int count=1;
    //当p=q的时候说明只有一个元素了，退出循环
    while(p!=q)
    {
        if(count==m)
        {
            //“出局”：删除当节点，并且让m等于该节点的data
            data=p->data;
            printf("Out:%d\n",data);
            q->next=p->next;
            p=q->next;
            count=1;
            m=data;
        }
        else
        {
            count++;
            q=p;
            p=q->next;
        }
    }
    printf("Out:%d\n",p->data);
    return 0;
}

int main()
{
    CLinkList L;
    Initial(&L);
    Create_Tail(&L);
    Josephus(&L);

    return 0;
}