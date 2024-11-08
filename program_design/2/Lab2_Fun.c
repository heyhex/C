#ifndef FUN_C
#define FUN_C

#include"Lab2_Fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)

int Is_Legal(char ch)
{
    if(ch>'9' || ch<'0')
        return 0;
    else
        return 1;
}

void Print(int num,char arr[num][3])
{
    printf("The number of data group:%d\n",num);
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

void File_In(int argc,char name[],char arr[][3])
{
    FILE *fp=fopen(name,"w+");
    if(!fp)
    {
        printf("File Failure!\n");
        exit(1);
    }
    fprintf(fp,"%d\n",argc);
    for(int i=0;i<argc;i++)
    {
        fprintf(fp,"%d,%d,%d\n",arr[i][0],arr[i][1],arr[i][2]);
    }
    if(feof(fp))
        printf("Success!");
    fclose(fp);
}

void CreateArr(int num,char arr[][3])
{
    srand((int)time(0));
    for(int i=0;i<num;i++)
        for(int j=0;j<3;j++)
            arr[i][j]=(unsigned int)random(10);
}

int Prompt()
{
    char input;
    printf("Enter the number of group:");
    scanf("%c",&input);
    if(input>'9' || input<'0')
    {
        printf("Wrong Enter!\n");
        return 0;
    }
    else
    {
        int num=(int)(input-'0');
        char arr[num][3];
        CreateArr(num,arr);
        File_In(num,"output.txt",arr);
        Print(num,arr);
        return 1;
    }
}

void Create(char *argv[])
{
    int num=(int)(*argv[1]-'0');
    char *name=(char *)argv[2];
    char arr[num][3];
    CreateArr(num,arr);
    File_In(num,name,arr);
    Print(num,arr);
}

#endif