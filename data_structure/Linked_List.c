#include<stdio.h>
#include<stdlib.h>

//单链表
typedef struct Node
{
    int data;
    struct Node *next;
}Node,*LinkList;

//初始化：创建一个头指针，并且使它的下一个节点为空
int Initial(LinkList *L)
{
    //分配内存
    (*L)=(LinkList)malloc(sizeof(Node));
    if(!L)
    {
        perror("Failed!");
        return 0;
    }
    //让头指针的下一个指向空，即完成了初始化
    (*L)->next=NULL;
    return 0;
}

//头插法：逆序输入数据
void Create1(LinkList *L)
{
    int i,n;
    LinkList p;
    //分配内存
    (*L)=(LinkList)malloc(sizeof(Node));
    if(!L)
        perror("Failed!");
    //先初始化L
    (*L)->next=NULL;
    printf("Enter the number of linklist :");
    scanf("%d",&n);
    printf("Enter the data :");
    for(i=0;i<n;i++)
    {
        //给下一个分配内存
        p=(LinkList)malloc(sizeof(Node));
        if(!p)
            perror("Failed!");
        scanf("%d",&p->data);
        //先指向后继，再接上前驱
        p->next=(*L)->next;
        (*L)->next=p;
    }
}

//尾插法：逆序生成
void Create2(LinkList *L)
{
	int i, n;
	LinkList p,r;
    //分配内存				
	(*L) = (LinkList)malloc(sizeof(Node));
    //r为计数指针
	r = *L;
	printf("Enter the number of linklist :");
	scanf("%d", &n);
	printf("Enter the data :");
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
        if(!p)
            perror("Failed!");
		scanf("%d", &p->data);
        //先指向后继，再移动r
		r->next = p;
		r = p;
	}
    //让尾指针（即当前的r）的下一个指向空
	r->next = NULL;
}

//获取元素，从第一个结点开始往后找，直到到达位置返回data
int Get(LinkList L,int i,int *e)
{
    int j=1;
    LinkList p;
    p=L->next;
    while(p && j<=i)
    {
        p=p->next;
        j++;
    }
    if(!p || j>i)
    {
        perror("Not Found");
        return 0;
    }
    *e=p->data;
    return 0;
}

//插入：本质是先改后继再改前驱
int Insert(LinkList *L,int i,int e)
{
    LinkList p=*L,s;
    int j=0;
    while(p && j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p || j>i-1)
    {
        perror("Not Found");
        return 0;
    }
    //分配新的内存
    s=(LinkList)malloc(sizeof(Node));
    s->data=e;
    //先指后继再指向前驱
    s->next=p->next;
    p->next=s;

    return 0;
}

//删除
int Delete(LinkList *L,int i,int *e)
{
    LinkList p=*L,q;
    int j=0;
    while(!(p->next) && j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!(p->next) || j>j-1)
    {
        perror("Not Found");
        return 0;
    }
    //q接收待删除的节点
    q=p->next;
    //将next修改为待删除结点的下一个结点
    p->next=q->next;
    //返回删除的数据
    *e=q->data;
    //记得释放结点
    free(q);

    return 0;
}

//清空链表：重置为空表
void Clear(LinkList *L)
{
    LinkList p;
    while((*L)->next)
    {
        p=(*L)->next;
        (*L)->next=p->next;
        free(p);
    }
    (*L)->next=NULL;
}

int main()
{

    LinkList L1,L2;
    Initial(&L1);
    Initial(&L2);
    int e1=0,e2=0;

    Create1(&L1);
    Create2(&L2);
    Get(L1,2,&e1);
    Insert(&L1,1,6);
    Delete(&L2,3,&e2);
    return 0;
}