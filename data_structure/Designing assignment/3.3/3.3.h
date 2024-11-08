#define Max_Size 2

//用共享栈来储存停车场里面的数据以及临时让道的车
typedef struct Car
{
    long number[2*Max_Size];
    int time[2*Max_Size];
    int top1;
    int top2;
}Parking_Lot;

//用链式队列储存排队的车
//结点结构：
typedef struct QNode
{
    long number;
    int time;
    struct QNode *next;
}QNode;

//队列结构
typedef struct
{
    QNode *front;
    QNode *rear;
}Sidewalk;