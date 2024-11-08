#include<stdio.h>
#include<stdlib.h>

#define List_Init_Size 80
#define ListIncrement 10

//线性表
typedef struct SqList
{
    int *p;//存储空间的基地址
    int length;
    int listsize;
}List;

//初始化线性表
////C语言里面没有引用！！！只能用指针
void Initial(List *L)
{
    L->p=(int *)malloc(sizeof(int)*List_Init_Size);
    if(!L->p)
        perror("Overflow");
    L->length=0;//长度初始化为0
    L->listsize=List_Init_Size;
}

//拓展长度：本质是创建一个新的长的线性表，再把原来的复制过去
void Extend(List *L)
{
    int *newbase=(int *)realloc(L->p,(L->length+ListIncrement)*sizeof(int));
    if(!newbase)
        perror("Not Enough Space");
    L->p=newbase;
    L->listsize+=ListIncrement;
}

//寻找元素：本质是创建一个指针指向首地址，一个计数器记录位置，进行遍历
void Locate(List L,int e)
{
    int *lp=L.p;
    for(int i=0;i<=L.length;i++)
    {
        if(*lp==e)
        {   printf("Location: %d\n",i);
            break;
        }
    }
    printf("Not Found!\n");
}

//另一种查找方式
////compare比较两个参数：相同则返回1，不相同就返回0
int compare(int e1, int e2)
		{if (e1==e2) 
			return 1;
		else 
		  	return 0;
		}
int Find(List L,int e,int (*compare)(int,int))
{
    int *lp=L.p;
    int i=1;
    //循环条件：i在长度内 && *p和e不相等（若相等的话则返回！1=0结束循环）
    while(i<=L.length && !(*compare)(*lp++,e))
        i++;
    if(i<=L.length)
        return i;
    else 
        return 0;
}

//插入:先找到第i-1个元素，从他之后的每一个向后移动，在插入新的元素
int Insert(List *L,int i,int e)
{
    int *q=&(L->p[i-1]);
    for(int *lp=&(L->p[L->length-1]);lp>=q;lp--)
    {
        *(lp+1)=*lp;
    }
    *q=e;
    L->length++;

    return 1;
}

//删除：同理，先找到第i-1个元素，后面的元素依次向前移动，最后储存一下被删除的元素万一有用
int Delete(List *L,int i,int e)
{
    if(i<1 || i>L->length)
    {
        perror("Not Found");
        return 0;
    }

    //需要注意这里是++lp，所以应该找到第i个元素的位置
    //如果是lp++，就需要定位到待删除元素的下一个元素   
    int *lp=&(L->p[i-1]);
    e=*lp;
    int *q=L->p+L->length-1;
    for(lp;lp<=q;++lp)
        *(lp-1)=*lp;
    L->length--;

    return 0;
}

//合并：创建两个指针，从（1，1）位置比较大小，填上之后指针后移
void Merge(List A,List B,List *C)
{
    int *a=A.p,*b=B.p;
    C->listsize=C->length=A.length+B.length;
    //分配内存
    int *c=C->p=(int *)malloc(sizeof(int)*C->listsize);
    if(!c)
    {
        perror("Overflow");
    }
    int *a_last=A.p+A.length-1;
    int *b_last=B.p+B.length-1;
    while(a<=a_last && b<=b_last)
    {
        if(*a<=*b)
            *c++=*a++;
        else
            *c++=*b++;
    }
    //下面两个while只会执行一个
    while(a<=a_last) 
            *c++=*a++;
    while(b<=b_last) 
            *c++=*b++;
}

int main()
{
    List L1,L2,L3;
    Initial(&L1);
    Initial(&L2);
    Initial(&L3);

    Extend(&L1);
    Insert(&L1,1,1);
    Delete(&L1,1,1);
    Locate(L1,1);
    Find(L1,1,compare);
    
    return 0;
}
