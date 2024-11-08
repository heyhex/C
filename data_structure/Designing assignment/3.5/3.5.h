//注意需要开容量为5
#define Max_Size 5

//利用循环队列
typedef struct 
{
    int data[Max_Size];
    int front,rear;
}CirQueueTp;

//这里采用空一个元素位置，以rear+1=front来判断队满