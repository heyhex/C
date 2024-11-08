#define Initial_Size 100
#define Increment 10

//坐标位置
typedef struct Position
{
    int x,y;
}Position;

//迷宫
typedef struct Maze
{
    int x,y;
    char arr[12][12];
}Maze;

//栈数据类型
typedef struct Elem
{
    Position p;
    int step;
    int direction;
}Elem;

//栈类型
typedef struct Stack
{
    Elem *base;
    Elem *top;
    int size;
}Stack;