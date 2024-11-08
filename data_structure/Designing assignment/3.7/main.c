#include"maze.c"

int main()
{
    Maze m;
    Initial_Maze(&m);
    Position start,end;
    printf("Enter the start position:");
    scanf("%d %d",&start.x,&start.y);
    printf("Enter the end position:");
    scanf("%d %d",&end.x,&end.y);
    Path(m,start,end);

    return 0;
}