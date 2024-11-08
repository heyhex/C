#include<stdio.h>
#include<math.h>
#include"1.5.h"

int main()
{   //提示输入自变量数目
    int num;
    printf("Enter the number of x: ");
    scanf("%d",&num);
    /*p=(int *)malloc(sizeof(int)*num);
    if(p==NULL)
    {
        perror("Failed: ");
        return 0;
    }
    for(int i=0;i<num;i++)
        p[i]=i;*/
    //写入文件
    FILE *fp=fopen("result.txt","w");
    //判断是否创建成功
    if(fp==NULL)
    {
        perror("Failed: ");
        return 0;
    }
    //利用fprintf写入
    for(int i=0;i<num;i++)
    {
        fprintf(fp,"x==%d\t%.2f\n",i,F1(i));
    }
    printf("Success!\n");

    //关闭文件
    fclose(fp);
    return 0;
}