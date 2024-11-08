#include<stdio.h>
//p[i]=j表示第i个皇后放在第i行第j列
int p[8]={-1};
int sum=0;

//判断是否能放
int Is_OK(int x,int y)
{
    //遍历前面的每一行
    for(int i=0;i<x;i++)
        //同一列，主副对角线都不行
        if(p[i]==y || x-i==y-p[i] || x-i+y-p[i]==0)
            //不可以返回0
            return 0;
    //可以的话返回1
    return 1;
}

void Print()
{
    printf("\n-----------No.%d-----------\n",sum);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(p[i]==j)
                printf("# ");
            else
                printf("* ");
        }
        printf("\n");
    }
    printf("------------End------------\n");
}

//前i-1都已经放好了棋子，现在考虑第i行棋子的位置
void queen(int i)
{
    //说明已经全部放进去
    if(i==8)
    {
        sum++;
        Print();
        return;
    }
    else
    {
        for(int j=0;j<8;j++)
        {
            if(Is_OK(i,j))
            {
                p[i]=j;
                queen(i+1);
            }
        }
    }
}

int main()
{
    queen(0);
}