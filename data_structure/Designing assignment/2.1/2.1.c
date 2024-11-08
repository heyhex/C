#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"2.1.h"

//初始化线性表
void Initial(StaffList *L)
{
    L->p=(Staff*)malloc(sizeof(Staff)*List_Size);
    if(!L->p)
        perror("Failed!");
    L->length=0;
    L->listsize=List_Size;
}

//增加长度：本质是“搬家”
void Extend(StaffList *L)
{
    Staff *newbase;
    newbase=(Staff*)realloc(L->p,(L->listsize+List_Increment)*sizeof(Staff));
    if(!newbase)
        perror("Failed!");
    L->p=newbase;
    L->listsize+=List_Increment;
}

//打印输出
void Show(StaffList L)
{
    int n=L.length;
    printf("\nSe_Num\tName\tNumber\tDuty\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%s\t%s\t%s\n",i+1,L.p[i].name,L.p[i].number,L.p[i].duty);
    }
    printf("\n");
}

//创建：依次存入数据，并且修改长度
void Create(StaffList *L)
{
    int n;
    printf("Enter the number of workers:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter NO.%d worker's name:",i+1);
        scanf("%s",L->p[i].name);
        printf("Enter NO.%d worker's number:",i+1);
        scanf("%s",L->p[i].number);
        printf("Enter NO.%d worker's duty:",i+1);
        scanf("%s",L->p[i].duty);
    }
    L->length=n;
    Show(*L);
}

//员工入职
int Insert(StaffList *L)
{
    if(L->length>=L->listsize)
    {
        //长度不够就扩容
        Extend(L);
    }
    Staff new={0};
    printf("Enter the name of new worker:");
    scanf("%s",new.name);
    printf("Enter the number of new worker:");
    scanf("%s",new.number);
    //需要判断工号有没有重复
    for(int i=0,length=L->length;i<length;i++)
    {
        while(strcmp(L->p[i].number,new.number)==0)
        {
            printf("Already occupied! Enter another number:");
            scanf("%s",new.number);
        }
    }
    printf("Enter the duty of new worker:");
    scanf("%s",new.duty);
    L->p[L->length]=new;
    L->length++;
    Show(*L);

    return 0;
}

//离职：通过工号查询来删除
int Delete(StaffList *L)
{
    char num[10];
    int i,n=0,length=L->length;
    printf("Enter the number of departing worker:");
    scanf("%s",num);
    Staff *p,*q;
    //遍历寻找相同的工号，当相同时推出循环
    for(i=0;i<length;i++)
        if(strcmp(L->p[i].number,num)==0)
        {
            printf("i=%d\n",i);
            //记录待删除元素的下一个元素的位置
            p=&(L->p[i+1]);
            //q是最后一个元素的位置
            q=L->p+L->length-1;
            for(p;p<=q;p++)
                *(p-1)=*p;
            break;
        }
    if(i==L->length)
    {
        printf("Not Found!");
        return 0;
    }
    else
    {
        L->length--;
        Show(*L);
        return 0;
    }
}

int Menu(StaffList *L)
{
    int num;
    printf("Welcome to the Management System!\n");
    while(1)
    {
        printf("Please Enter a Number!\n");
        printf("1.Create\n2.Worker Entry\n3.Worker Department\n");
        printf("4.Print All Information\n0.Exit System\n\n");
        printf("Enter the number:");
        scanf("%d",&num);
        switch (num)
        {
        case 1:
            Create(L);
            break;
        case 2:
            Insert(L);
            break;
        case 3:
            Delete(L);
            break;
        case 4:
            Show(*L);
            break;
        case 0:
            return 0;
            break;
        default:
        printf("Wrong number! Enter again:");
    }
    }
    
}

int main()
{
    StaffList L;
    Initial(&L);
    Menu(&L);

    return 0;
}