#define List_Init_Size 80
#define ListIncrement 10

//线性表
typedef struct SqList
{
    int *p;//存储空间的基地址
    int length;
    int listsize;
}List;