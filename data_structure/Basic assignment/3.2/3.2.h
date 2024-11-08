//顺序存储结构
#define Max_Size 80
typedef struct SqStack
{
    char *data;
    int top;
}SqStack;

//顺序存储2：类似线性表的顺序映像
#define STACK_INIT_SIZE 100; 
#define STACKINCREMENT 10;  
typedef struct{
    char *base;    
    char *top;  //指向栈顶的下一个位置
    int size;    
}SqStack2;

//共享存储结构
typedef struct SqDulStack
{
    char data[Max_Size];
    int top1,top2;
}SqDulStack;

//链式存储
typedef struct SNode
{
    char data;
    struct SNode *next;
}SNode,*LinkStack;