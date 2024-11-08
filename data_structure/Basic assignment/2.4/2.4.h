#define List_Init_Size 80
#define ListIncrement 10

//线性表
typedef struct SqList
{
    int a[List_Init_Size];
    int length;
}List;