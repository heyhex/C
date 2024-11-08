#include<stdio.h>
#include<stdlib.h>
#include"3.3.h"

//初始化
void InitialStack(Parking_Lot *S)
{
    S->top1=-1;
    S->top2=2*Max_Size;
    for(int i=0;i<Max_Size;i++)
    {
        S->number[i]=0;
        S->time[i]=0;
    }
}

//进栈
int PushStack(Parking_Lot *S,int Snumber,long number,int time)
{
    if(S->top1+1==S->top2)
    {
        printf("Full!\n");;
        return 0;
    }
    if(Snumber==1)
    {
        S->top1++;
        S->number[S->top1]=number;
        S->time[S->top1]=time;
    }
    else if(Snumber==2)
    {
        S->top2--;
        S->number[S->top2]=number;
        S->time[S->top2]=time;
    }
    return 1;
}

//出栈
int PopStack(Parking_Lot *S,int Snumber,long *number,int *time)
{
    if(Snumber==1)
    {
        if(S->top1==-1)
        {
            printf("Already Empty!\n");
            return 0;
        }
        *number=S->number[S->top1];
        *time=S->time[S->top1];
        S->top1--;
    }
    else if(Snumber==2)
    {
        if(S->top2==2*Max_Size)
        {
            printf("Already Empty!\n");
            return 0;
        }
        *number=S->number[S->top2];
        *time=S->time[S->top2];
        S->top2++;
    }
    return 1;
}

//初始化
void InitailQueue(Sidewalk *Q)
{
    Q->front=(QNode*)malloc(sizeof(QNode));
    Q->rear=(QNode*)malloc(sizeof(QNode));
    if(!Q->front || !Q->rear)
        exit(1);
    Q->rear=Q->front;
    Q->front->next=NULL;
}

//入队
int InQueue(Sidewalk *Q,int number,int time)
{
    QNode *q=(QNode*)malloc(sizeof(QNode));
    if(!q)
        exit(1);
    q->number=number;
    q->time=time;
    q->next=NULL;
    Q->rear->next=q;
    Q->rear=q;

    return 1;
}

//出队
int OutQueue(Sidewalk *Q,long *number,int *time)
{
    //首先判断是不是为空
    if(Q->front==Q->rear)
    {
        printf("Empty!\n");
        return 0;
    }
    QNode *q;
    q=Q->front->next;
    *number=q->number;
    *time=q->time;
    Q->front->next=q->next;
    if(Q->rear==q)
        Q->rear=Q->front;
    free(q);
    
    return 1;
}

//打印输出
void ShowList(Parking_Lot S)
{
    printf("\n--------Car List--------\n");
    if(S.top1==-1)
    {
        printf("Empty!\n");
    }
    else
    {
        printf("Se_Num\tCar_Num\tTime_In\n");
        for(int i=0;i<=S.top1;i++)
        {
            printf("%d\t%ld\t%d\n",i+1,S.number[i],S.time[i]);
        }
        printf("--------End List--------\n\n");
    }
}

//寻找车辆位置：返回车辆的下标
int Find(Parking_Lot S,long number,int time)
{
    int i;
    for(i=0;i<=S.top1;i++)
    {
        if(S.number[i]==number)
        {
            //如果找到了车辆之后就返回下标
            return i;
            break;
        }
    }
    //如果遍历完之后没有找到就返回-1
    if(i>S.top1)
    {
        printf("Not Found!\n");
        return -1;
    }
}

//收费
int Charge(int time_in,int time_out)
{
    return (time_out-time_in)*10;
}

//到达
int Arrival(Parking_Lot *S,Sidewalk *Q,long number,int time)
{
    if(S->top1<Max_Size-1)
    {
        PushStack(S,1,number,time);
        printf("Success In!\n");
        return 1;
    }
    else if(S->top1==Max_Size-1)
    {
        printf("Waiting!\n");
        InQueue(Q,number,time);
        return 0;
    }
}

//离开
int Departure(Parking_Lot *S,Sidewalk *Q,long number,int time)
{
    //先寻找
    int n=Find(*S,number,time);
    if(n==-1)
    {
        printf("Failed to Leave!\n");
        return -1;
    }
    else
    {
        //首先打印输出收费
        int i,price=0;
        long number_=0,number_out=0;
        int time_=0,time_in=0;
        //将要离开的车的后面的车依次移动到第二个栈里面
        for(i=S->top1;i>n;i--)
        {
            PopStack(S,1,&number_,&time_);
            PushStack(S,2,number_,time_);
        }
        //当前车辆出栈，记录进栈时间
        PopStack(S,1,&number_out,&time_in);
        price=Charge(time_in,time);
        printf("--------Charge--------\n");
        printf("Se_Num\tCar_Num\tTime_in\tTime_out Price\n");
        printf("%d\t%ld\t%d\t%d\t %d\n",n+1,number_out,time_in,time,price);
        printf("---------End----------\n\n");

        //然后将暂时存储的车放回去，并且进一辆新车
        for(i=S->top2;i<2*Max_Size;i++)
        {
            PopStack(S,2,&number_,&time_);
            PushStack(S,1,number_,time_);
        }
        //当有空位的时候
        if(S->top1<Max_Size)
        {
            if(Q->front==Q->rear)
                printf("No New Car In!\n");
            //并且有车在排队的时候入栈
            else
            {
                OutQueue(Q,&number_,&time_);
                PushStack(S,1,number_,time_);
                printf("New Car In!\n\n");
                ShowList(*S);
            }
        }
    }
    return 1;
}

void Manegement()
{
    Parking_Lot S;
    Sidewalk Q;
    InitialStack(&S);
    InitailQueue(&Q);
    
    char state;
    long number;
    int time;
    printf("Welcome to The Parking Lot Management System!\n");
    printf("A:Arrival\tD:Departure\tS:Show list\tE:End\n");
    printf("Enter [Statement] [Car Number] [Time] :\n");

    while (1) 
    {
        // 修复了输入处理，确保 %c 读取正确（由chatgpt指出的错误）
        if (scanf(" %c%ld%d", &state, &number, &time) != 3) {
            printf("Invalid input format! Please enter again.\n");
            // 清空输入缓冲区以防止错误重复
            while (getchar() != '\n'); 
            continue;  // 重新获取输入
        }

        switch (state) {
        case 'A':  // 车辆到达
            Arrival(&S, &Q, number, time);
            break;
        case 'D':  // 车辆离开
            Departure(&S, &Q, number, time);
            break;
        case 'S':  // 显示停车场信息
            ShowList(S);
            break;
        case 'E':  // 退出程序
            printf("End of Management System!\n");
            return;  // 退出管理系统
        default:
            printf("Invalid command! Please enter again.\n");
            break;
        }
    }
}

int main()
{
    Manegement();

    return 0;
}