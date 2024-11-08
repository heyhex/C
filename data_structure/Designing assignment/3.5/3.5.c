#include<stdio.h>
#include<stdlib.h>
#include"3.5.h"

//初始化
void Initial(CirQueueTp *Q)
{
    for(int i=0;i<Max_Size;i++)
        Q->data[i]=0;
    Q->front=Q->rear=0;
}

//入队
int Enter(CirQueueTp *Q,int e)
{
    if((Q->rear+1)%Max_Size==Q->front)
    {
        printf("Full!\n");
        return 0;
    }
    else
    {
        Q->data[Q->rear]=e;
        Q->rear=(Q->rear+1)%Max_Size;
        return 1;
    }
}

//出队
int Depart(CirQueueTp *Q,int *e)
{
    if(Q->rear==Q->front)
    {
        printf("Empty!\n");
        return 0;
    }
    else
    {
        *e=Q->data[Q->front];
        Q->front=(Q->front+1)%Max_Size;
        return 1;
    }
}

//题目解答：k阶，最大为max
void Fibonacci(int k,int max)
{
    int f[100]={0};
    CirQueueTp Q;
    Initial(&Q);
    int n=0,out=0,in=0;

    //首先初始化前k-1个值为0,第k个为1
    for(int i=0;i<k-1;i++)
    {
        Enter(&Q,0);
    }
    Enter(&Q,1);

    //然后依次进队出队
    while(Q.data[Q.front]<=max)
    {
        //首先获取下一个数
        for(int j=Q.front,count=1;count<=k;j++,count++)
        {
            if(j%Max_Size==0)
                j=0;
            in+=Q.data[j];
        }
        //然后先出队再入队,存入数据
        Depart(&Q,&out);
        f[n]=out;
        Enter(&Q,in);
        n++;
        in=0;
    }

    //打印输出数列
    for(int i=0;i<n;i++)
        printf("%d\n",f[i]);
}

int main()
{
    Fibonacci(4,200);

    return 0;
}