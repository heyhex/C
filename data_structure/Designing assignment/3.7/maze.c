#include<stdio.h>
#include"stack.c"

//迷宫操作
//自动生成一个迷宫（暂时不会）
//提示输入一个二维数组创建迷宫
void Initial_Maze(Maze *m)
{
    int x,y;
    printf("Enter the row and column:");
    scanf("%d %d",&x,&y);
    m->x=x+2;
    m->y=y+2;

    

    //输入迷宫：障碍为1
    printf("Enter the maze:\n");
	for(int i=1;i<=x;i++)
    {
        for(int j=1;j<=y;j++)
        {
            scanf("%d",&m->arr[i][j]);
        }
    }//外围为1
    for(int i=0;i<y+2;i++)
        m->arr[0][i]=m->arr[x+1][i]=1;
    for(int i=0;i<x+2;i++)
        m->arr[i][0]=m->arr[i][y+1]=1;
}

//判断是否可以通过
int Pass(Maze m,Position p)
{
    //只有是0的时候可以走，其他时候不可以通过
    if(m.arr[p.x][p.y]==0)
        return 1;
    else
        return 0;
}

//留下可以通过的路径
void FootPrint(Maze *m,Position p,int step)
{
    m->arr[p.x][p.y]=step;
}

//留下不能通过的路径：用-2标记
void MarkPrint(Maze *m,Position p)
{
    m->arr[p.x][p.y]=-2;
}

//顺时针寻找洗一个路径
Position Next_Position(Position cur_position,int dir)
{
    Position next;
    int x=cur_position.x;
    int y=cur_position.y;
    if(dir==1)
    {
        next.x=x;
        next.y=y+1;
    }
    else if(dir==2)
    {
        next.x=x+1;
        next.y=y;
    }
    else if(dir==3)
    {
        next.x=x;
        next.y=y-1;
    }
    else if(dir==4)
    {
        next.x=x-1;
        next.y=y;
    }
    else
        printf("Wrong Direction!]n");
    return next;
}

//打印路径
void Show(Maze m)
{
    for(int i=1;i<m.x-1;i++)
    {
        for(int j=1;j<m.y-1;j++)
        {
            if(m.arr[i][j]<0)
                printf("@ ");
            else if(m.arr[i][j]==0)
                printf("  ");
            else if(m.arr[i][j]==1)
                printf("# ");
            else
                printf("* ");
        }
        printf("\n");
    }
}

//寻找路径
void Path(Maze m,Position start,Position end)
{
    //如果找到一条路径就放在栈里
    Stack S;
    Initial(&S);
    Position cur_position=start;
    int cur_step=2,is_found=0;
    
    //方向东南西北：1234
    //先探索第一步：因此用do-while循环
    do
    {
        //当前位置可以通过时
        if(Pass(m,cur_position))
        {
            //留下足迹
            FootPrint(&m,cur_position,cur_step);
            //并且入栈
            Elem temp;
            temp.p=cur_position;
            temp.step=cur_step;
            temp.direction=1;
            Push(&S,temp);
            //如果到达了终点就找到了路径
            if(cur_position.x==end.x && cur_position.y==end.y)
            {
                is_found=1;
                break;
            }
            //如果没有到终点就下一步
            else
            {
                cur_position=Next_Position(cur_position,1);
                cur_step++;
            }
        }
        //如果当前位置不能通过的话
        else
        {
            //弹出当前的位置，并且记录
            if(!Empty(S))
            {
                //接受退出来的Position类型的数据
                Elem e;
                Pop(&S,&e);
                //当四个方向都寻找完之后
                while(e.direction==4 && !Empty(S))
                {
                    //标记为不可行的路径，并且再退一步
                    MarkPrint(&m,e.p);
                    Pop(&S,&e);
                    cur_step--;
                }
                //当还有方向没有探索的时候，换下一个方向
                if(e.direction<4)
                {
                    e.direction++;
                    Push(&S,e);
                    //并且将当前位置设定在下一个
                    cur_position=Next_Position(e.p,e.direction);
                }
            }
        }
    }
    //循环条件为没有找到并且栈非空
    while(!is_found && !Empty(S));

    //最后打印输出
    printf("\n");
    if(is_found==1)
        Show(m);
    else
        printf("Not Found!\n");
}